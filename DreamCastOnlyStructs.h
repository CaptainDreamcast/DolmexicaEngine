typedef struct{

BackGroundInnerAnimationStruct Data;
pvr_ptr_t Texture[BackGroundFrameAmountMax];

} BackGroundAnimationStruct;

typedef struct{

pvr_ptr_t Texture[CharacterTextureBufferAmount];
uint8 WhichTextureInUse;

} CharacterTextureStruct;
