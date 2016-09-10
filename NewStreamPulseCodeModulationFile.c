
#include <assert.h>
#include <dc/g2bus.h>
#include <dc/spu.h>
#include <dc/sound/sound.h>

#include "../kernel/arch/dreamcast/sound/arm/aica_cmd_iface.h"

typedef struct strchan {
int	ch[2];
int	last_write_pos;	
int	curbuffer;	
int	buffer_size;	
uint32	spu_ram_sch[2];
snd_stream_callback_t get_data;
TAILQ_HEAD(filterlist, filter) filters;
int	stereo;
int	frequency;
int 	queueing;
volatile int	initted;
} strchan_t;

static strchan_t streams[SND_STREAM_MAX] = { { { 0 } } };

#define SPU_RAM_BASE            0xa0800000

#define CHECK_HND(x) do { \
assert( (x) >= 0 && (x) < SND_STREAM_MAX ); \
assert( streams[(x)].initted ); \
} while(0)

int16* StereoSeparationBuffer[2] = { NULL, NULL };

kthread_t* StreamingThreadIdentifier;
file_t StreamingInputFile;
//uint8* StreamingBuffer = NULL;
uint8 StreamingBuffer[SND_STREAM_BUFFER_MAX*2];
uint8 MusicIsPlaying;



void EndStreaming(snd_stream_hnd_t StreamingHandler){

//filter_t* FilterThing, AnotherFilterThing;
CHECK_HND(StreamingHandler);

if(!streams[StreamingHandler].initted) return;

//FilterThing = TAILQ_FIRST(&streams[StreamingHandler].filters);
//while(FilterThing){
//AnotherFilterThing = TAILQ_NEXT(FilterThing, lent);
//free(FilterThing);
//FilterThing = AnotherFilterThing;
//}
//TAILQ_INIT(&streams[StreamingHandler].filters);


AICA_CMDSTR_CHANNEL(tmp, cmd, chan);
if (!streams[StreamingHandler].get_data) return;

cmd->cmd = AICA_CMD_CHAN;
cmd->timestamp = 0;
cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
cmd->cmd_id = streams[StreamingHandler].ch[0];
chan->cmd = AICA_CH_CMD_STOP;
snd_sh4_to_aica(tmp, cmd->size);

cmd->cmd_id = streams[StreamingHandler].ch[1];
snd_sh4_to_aica(tmp, AICA_CMDSTR_CHANNEL_SIZE);

snd_sfx_chn_free(streams[StreamingHandler].ch[0]);
snd_sfx_chn_free(streams[StreamingHandler].ch[1]);

free(StereoSeparationBuffer[0]);
free(StereoSeparationBuffer[1]);
StereoSeparationBuffer[0] = NULL;
StereoSeparationBuffer[1] = NULL;

snd_mem_free(streams[StreamingHandler].spu_ram_sch[0]);
snd_mem_free(streams[StreamingHandler].spu_ram_sch[1]);
streams[StreamingHandler].initted = 0;
memset(streams+StreamingHandler, 0, sizeof(streams[0]));
}

void SetStreamingDataRetrievalFunction(snd_stream_hnd_t StreamingHandler, snd_stream_callback_t StreamingDataRetrievalFunction){
CHECK_HND(StreamingHandler);
streams[StreamingHandler].get_data = StreamingDataRetrievalFunction;
}

snd_stream_hnd_t AllocateStreamingStuff(snd_stream_callback_t StreamingDataRetrievalFunction, int BufferSize) {

int DirtyDeedsDoneDirtCheap, ThreadingThingWhichDoesSomething;
snd_stream_hnd_t StreamingHandler;


StreamingHandler = -1;
ThreadingThingWhichDoesSomething = irq_disable();
for (DirtyDeedsDoneDirtCheap=0; DirtyDeedsDoneDirtCheap<SND_STREAM_MAX; DirtyDeedsDoneDirtCheap++) {
if (!streams[DirtyDeedsDoneDirtCheap].initted) {
StreamingHandler = DirtyDeedsDoneDirtCheap;
break;
}
}

if (StreamingHandler != -1) streams[StreamingHandler].initted = 1;
irq_restore(ThreadingThingWhichDoesSomething);
if (StreamingHandler == -1) return SND_STREAM_INVALID;

streams[StreamingHandler].buffer_size = BufferSize;
streams[StreamingHandler].queueing = 0;
	
SetStreamingDataRetrievalFunction(StreamingHandler, StreamingDataRetrievalFunction);

TAILQ_INIT(&streams[StreamingHandler].filters);

streams[StreamingHandler].spu_ram_sch[0] = snd_mem_malloc(streams[StreamingHandler].buffer_size*2);
streams[StreamingHandler].spu_ram_sch[1] = snd_mem_malloc(streams[StreamingHandler].buffer_size*2);
//streams[StreamingHandler].spu_ram_sch[1] = streams[StreamingHandler].spu_ram_sch[0] + streams[StreamingHandler].buffer_size;

streams[StreamingHandler].ch[0] = snd_sfx_chn_alloc();
streams[StreamingHandler].ch[1] = snd_sfx_chn_alloc();
printf("Channels Used: (%d)/(%d)\n", streams[StreamingHandler].ch[0], streams[StreamingHandler].ch[1]);

return StreamingHandler;
}

void SeparateChannels(void *SampleBuffer, int BufferSize, int Stereo, uint16 BitSize) {

register int	DirtyDeedsDoneDirtCheap, BurningDownTheHouse, ReadyToRock;

if (Stereo){

if(BitSize == 16){
register int16	*SourceBuffer, *DestinationBuffer;

SourceBuffer = (int16*)SampleBuffer;
DestinationBuffer = StereoSeparationBuffer[0];
DirtyDeedsDoneDirtCheap = 0; 
BurningDownTheHouse = 0; 
ReadyToRock = BufferSize / 2;

do{
*DestinationBuffer = *SourceBuffer;
DestinationBuffer++; 
SourceBuffer+=2; 
ReadyToRock--;
} while (ReadyToRock > 0);

SourceBuffer = (int16*)SampleBuffer; 
SourceBuffer++;
DestinationBuffer = StereoSeparationBuffer[1];
DirtyDeedsDoneDirtCheap = 1; 
BurningDownTheHouse = 0; 
ReadyToRock = BufferSize / 2;

do {
*DestinationBuffer = *SourceBuffer;
DestinationBuffer++; 
SourceBuffer+=2; 
ReadyToRock--;
DirtyDeedsDoneDirtCheap+=2; 
BurningDownTheHouse++;
} while (ReadyToRock > 0);

}
else{
register uint8	*SourceBuffer, *DestinationBuffer;

SourceBuffer = (uint8*)SampleBuffer;
DestinationBuffer = (uint8*)StereoSeparationBuffer[0];
DirtyDeedsDoneDirtCheap = 0; 
BurningDownTheHouse = 0; 
ReadyToRock = BufferSize / 2;

do{
*DestinationBuffer = *SourceBuffer;
DestinationBuffer++; 
SourceBuffer+=2; 
ReadyToRock--;
} while (ReadyToRock > 0);

SourceBuffer = (uint8*)SampleBuffer; 
SourceBuffer++;
DestinationBuffer = (uint8*)StereoSeparationBuffer[1];
DirtyDeedsDoneDirtCheap = 1; 
BurningDownTheHouse = 0; 
ReadyToRock = BufferSize / 2;

do {
*DestinationBuffer = *SourceBuffer;
DestinationBuffer++; 
SourceBuffer+=2; 
ReadyToRock--;
DirtyDeedsDoneDirtCheap+=2; 
BurningDownTheHouse++;
} while (ReadyToRock > 0);
}

} 
else{
memcpy(StereoSeparationBuffer[0], SampleBuffer, BufferSize);
memcpy(StereoSeparationBuffer[1], SampleBuffer, BufferSize);
}
}

void FillStreamingBuffer(StreamingStruct StreamingData) {
void *SampleBuffer;
int SamplesGotten;

CHECK_HND(StreamingData.StreamingHandler);

if (!streams[StreamingData.StreamingHandler].get_data) return;

if (streams[StreamingData.StreamingHandler].stereo) SampleBuffer = streams[StreamingData.StreamingHandler].get_data(StreamingData.StreamingHandler, streams[StreamingData.StreamingHandler].buffer_size, &SamplesGotten);
else SampleBuffer = streams[StreamingData.StreamingHandler].get_data(StreamingData.StreamingHandler, streams[StreamingData.StreamingHandler].buffer_size/2, &SamplesGotten);

//process_filters(StreamingData.StreamingHandler, &SampleBuffer, &SamplesGotten);
SeparateChannels(SampleBuffer, (streams[StreamingData.StreamingHandler].buffer_size/2), streams[StreamingData.StreamingHandler].stereo, StreamingData.WaveHeaderData.BitSize);
spu_memload(streams[StreamingData.StreamingHandler].spu_ram_sch[0] + (streams[StreamingData.StreamingHandler].buffer_size/2)*0, (uint8*)StereoSeparationBuffer[0], streams[StreamingData.StreamingHandler].buffer_size/2);
spu_memload(streams[StreamingData.StreamingHandler].spu_ram_sch[1] + (streams[StreamingData.StreamingHandler].buffer_size/2)*0, (uint8*)StereoSeparationBuffer[1], streams[StreamingData.StreamingHandler].buffer_size/2);

if (streams[StreamingData.StreamingHandler].stereo) SampleBuffer = streams[StreamingData.StreamingHandler].get_data(StreamingData.StreamingHandler, streams[StreamingData.StreamingHandler].buffer_size, &SamplesGotten);
else SampleBuffer = streams[StreamingData.StreamingHandler].get_data(StreamingData.StreamingHandler, streams[StreamingData.StreamingHandler].buffer_size/2, &SamplesGotten);

//process_filters(StreamingData.StreamingHandler, &SampleBuffer, &SamplesGotten);
SeparateChannels(SampleBuffer, (streams[StreamingData.StreamingHandler].buffer_size/2), streams[StreamingData.StreamingHandler].stereo, StreamingData.WaveHeaderData.BitSize);

spu_memload(streams[StreamingData.StreamingHandler].spu_ram_sch[0] + (streams[StreamingData.StreamingHandler].buffer_size/2)*1, (uint8*)StereoSeparationBuffer[0], streams[StreamingData.StreamingHandler].buffer_size/2);
spu_memload(streams[StreamingData.StreamingHandler].spu_ram_sch[1] + (streams[StreamingData.StreamingHandler].buffer_size/2)*1, (uint8*)StereoSeparationBuffer[1], streams[StreamingData.StreamingHandler].buffer_size/2);


streams[StreamingData.StreamingHandler].last_write_pos = 0;
streams[StreamingData.StreamingHandler].curbuffer = 0;
}


void StartStreaming(StreamingStruct StreamingData){

AICA_CMDSTR_CHANNEL(tmp, cmd, chan);
CHECK_HND(StreamingData.StreamingHandler);

if (!streams[StreamingData.StreamingHandler].get_data) return;

if (StereoSeparationBuffer[0] == NULL){
StereoSeparationBuffer[0] = memalign(32, (SND_STREAM_BUFFER_MAX/2));
StereoSeparationBuffer[1] = memalign(32, (SND_STREAM_BUFFER_MAX/2));
}

streams[StreamingData.StreamingHandler].stereo = StreamingData.WaveHeaderData.Channels-1;
streams[StreamingData.StreamingHandler].frequency = StreamingData.WaveHeaderData.Frequency;

printf("Stereo: (%d)\n", streams[StreamingData.StreamingHandler].stereo);
printf("Frequency: (%d)\n", streams[StreamingData.StreamingHandler].frequency);
printf("Format: (%d)\n", StreamingData.WaveHeaderData.Format);

snd_sh4_to_aica_stop();
FillStreamingBuffer(StreamingData);

if(StreamingData.WaveHeaderData.Format == FormatADPCM) chan->type = AICA_SM_ADPCM;
else if(StreamingData.WaveHeaderData.BitSize == 16) chan->type = AICA_SM_16BIT;
else chan->type = AICA_SM_8BIT;

cmd->cmd = AICA_CMD_CHAN;
cmd->timestamp = 0;
cmd->size = AICA_CMDSTR_CHANNEL_SIZE;
cmd->cmd_id = streams[StreamingData.StreamingHandler].ch[0];
chan->cmd = AICA_CH_CMD_START | AICA_CH_START_DELAY;
chan->base = streams[StreamingData.StreamingHandler].spu_ram_sch[0];
chan->length = (SND_STREAM_BUFFER_MAX/2);
chan->loop = 1;
chan->loopstart = 0;
chan->loopend = (SND_STREAM_BUFFER_MAX/2);
chan->freq = streams[StreamingData.StreamingHandler].frequency;
chan->vol = (VolumeCDDA*255)/15;
chan->pan = 0;
snd_sh4_to_aica(tmp, cmd->size);

cmd->cmd_id = streams[StreamingData.StreamingHandler].ch[1];
chan->base = streams[StreamingData.StreamingHandler].spu_ram_sch[1];
chan->pan = 255;
snd_sh4_to_aica(tmp, cmd->size);

cmd->cmd_id = ((1 << streams[StreamingData.StreamingHandler].ch[0]) | (1 << streams[StreamingData.StreamingHandler].ch[1]));
chan->cmd = AICA_CH_CMD_START | AICA_CH_START_SYNC;
snd_sh4_to_aica(tmp, cmd->size);


snd_sh4_to_aica_start();
}



int StreamingCheckForSamples(StreamingStruct* StreamingData){

uint32 SamplesInBuffer;
uint32 CurrentBufferPosition;
uint32 SamplesNeeded;
uint32 SizeNeeded;
uint32 PositionFirstChannel, PositionSecondChannel;
uint32 LastWritePositionBytes;
int SamplesGotten;
void* SampleBuffer;

if(StreamingData->Counter > 3){

CHECK_HND(StreamingData->StreamingHandler);
if (!streams[StreamingData->StreamingHandler].get_data) return -1;

SampleBuffer = NULL;

PositionFirstChannel = g2_read_32(SPU_RAM_BASE + AICA_CHANNEL(streams[StreamingData->StreamingHandler].ch[0]) + offsetof(aica_channel_t, pos));
PositionSecondChannel = g2_read_32(SPU_RAM_BASE + AICA_CHANNEL(streams[StreamingData->StreamingHandler].ch[1]) + offsetof(aica_channel_t, pos));

if(StreamingData->WaveHeaderData.Format == FormatADPCM){
SamplesInBuffer = streams[StreamingData->StreamingHandler].buffer_size*2;
LastWritePositionBytes = streams[StreamingData->StreamingHandler].last_write_pos/2;
}
else if(StreamingData->WaveHeaderData.BitSize == 16){
SamplesInBuffer = streams[StreamingData->StreamingHandler].buffer_size/2;
LastWritePositionBytes = streams[StreamingData->StreamingHandler].last_write_pos*2;
}
else{
SamplesInBuffer = streams[StreamingData->StreamingHandler].buffer_size;
LastWritePositionBytes = streams[StreamingData->StreamingHandler].last_write_pos;
}

if (PositionFirstChannel >= SamplesInBuffer) {
printf("snd_stream_poll: chan0(%d).pos = %ld (%08lx)\n", streams[StreamingData->StreamingHandler].ch[0], PositionFirstChannel, PositionFirstChannel);
return -1;
}
	
CurrentBufferPosition = (PositionFirstChannel < PositionSecondChannel)?(PositionFirstChannel):(PositionSecondChannel);

if(streams[StreamingData->StreamingHandler].last_write_pos <= CurrentBufferPosition) SamplesNeeded = CurrentBufferPosition - streams[StreamingData->StreamingHandler].last_write_pos;
else SamplesNeeded = SamplesInBuffer - streams[StreamingData->StreamingHandler].last_write_pos;
SamplesNeeded &= ~0x7ff;

if(StreamingData->WaveHeaderData.Format == FormatADPCM) SizeNeeded = SamplesNeeded/2;
else if(StreamingData->WaveHeaderData.BitSize == 16) SizeNeeded = SamplesNeeded*2;
else SizeNeeded = SamplesNeeded;

if(streams[StreamingData->StreamingHandler].stereo) SizeNeeded*=2;

//printf("\n");
//printf("CurrentBufferPosition %6i, SamplesInBuffer        %6i\n", CurrentBufferPosition, SamplesInBuffer); 
//printf("SamplesNeeded         %6i, SizeNeeded             %6i\n", SamplesNeeded, SizeNeeded); 
//printf("LastWritePosition     %6i, LastWritePositionBytes %6i\n", streams[StreamingData->StreamingHandler].last_write_pos, LastWritePositionBytes); 
//printf("\n");

if(SizeNeeded > 0 && SizeNeeded < SND_STREAM_BUFFER_MAX){
SampleBuffer = streams[StreamingData->StreamingHandler].get_data(StreamingData->StreamingHandler, SizeNeeded, &SamplesGotten);
//process_filters(StreamingData->StreamingHandler, &SampleBuffer, &SamplesGotten);
if(SamplesGotten < SizeNeeded) return(-1);


if(streams[StreamingData->StreamingHandler].stereo) SizeNeeded/=2;

if (SampleBuffer == NULL){
spu_memset(streams[StreamingData->StreamingHandler].spu_ram_sch[0] + LastWritePositionBytes, 0, SizeNeeded);
spu_memset(streams[StreamingData->StreamingHandler].spu_ram_sch[1] + LastWritePositionBytes, 0, SizeNeeded);
return(-3);
}

SeparateChannels(SampleBuffer, SizeNeeded, streams[StreamingData->StreamingHandler].stereo, StreamingData->WaveHeaderData.BitSize);
spu_memload(streams[StreamingData->StreamingHandler].spu_ram_sch[0] + LastWritePositionBytes, (uint8*)StereoSeparationBuffer[0], SizeNeeded);
spu_memload(streams[StreamingData->StreamingHandler].spu_ram_sch[1] + LastWritePositionBytes, (uint8*)StereoSeparationBuffer[1], SizeNeeded);

streams[StreamingData->StreamingHandler].last_write_pos += SamplesNeeded;
if(streams[StreamingData->StreamingHandler].last_write_pos >= SamplesInBuffer) streams[StreamingData->StreamingHandler].last_write_pos -= SamplesInBuffer;
}

StreamingData->Counter = 0;
}
else StreamingData->Counter++;

return(1);
}


void* StreamingDataRetrievalFunction(snd_stream_hnd_t StreamingHandler, int DataSizeRequested, int* DataSizeRetrieved){


*DataSizeRetrieved = FileRead(StreamingInputFile, StreamingBuffer, DataSizeRequested);

//printf("DataSizeRequested: (%d)\n", DataSizeRequested);
//printf("DataSizeRetrieved: (%d)\n", *DataSizeRetrieved);

if(*DataSizeRetrieved < DataSizeRequested){
FileSeek(StreamingInputFile, 0x32, SEEK_SET);
FileRead(StreamingInputFile, StreamingBuffer+(*DataSizeRetrieved), DataSizeRequested-(*DataSizeRetrieved));
*DataSizeRetrieved = DataSizeRequested;
}

return(StreamingBuffer);
}




void StopStreamingPulseCodeModulationFile(StreamingStruct* StreamingData){


FileClose(StreamingInputFile);

EndStreaming(StreamingData->StreamingHandler);
}

StreamingStruct StreamPulseCodeModulationFile(char FileDir[]){

StreamingStruct StreamingData;

printf("FileDir: (%s)\n", FileDir);
StreamingInputFile = FileOpen(FileDir, O_RDONLY);

FileSeek(StreamingInputFile, 0, SEEK_SET);
FileRead(StreamingInputFile, &StreamingData.WaveHeaderData, sizeof(WaveHeaderStruct));

if(StreamingData.WaveHeaderData.Format == FormatADPCM) StreamingData.BufferSize = SND_STREAM_BUFFER_MAX/4;
else if(StreamingData.WaveHeaderData.BitSize == 16) StreamingData.BufferSize = SND_STREAM_BUFFER_MAX;
else StreamingData.BufferSize = SND_STREAM_BUFFER_MAX/2;

StreamingData.StreamingHandler = AllocateStreamingStuff(StreamingDataRetrievalFunction, StreamingData.BufferSize);

StartStreaming(StreamingData);

StreamingData.Counter = 0;

return(StreamingData);
}