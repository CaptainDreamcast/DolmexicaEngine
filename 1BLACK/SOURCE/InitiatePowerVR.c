void InitiatePowerVR(){

pvr_init_params_t DolmexicaRenderingStuff;

DolmexicaRenderingStuff.opb_sizes[0] = 16;
DolmexicaRenderingStuff.opb_sizes[1] = 0;
DolmexicaRenderingStuff.opb_sizes[2] = 16;
DolmexicaRenderingStuff.opb_sizes[3] = 0;
DolmexicaRenderingStuff.opb_sizes[4] = 16;

DolmexicaRenderingStuff.vertex_buf_size = 512*1024;

DolmexicaRenderingStuff.dma_enabled = 0;

DolmexicaRenderingStuff.fsaa_enabled = 0;

pvr_init(&DolmexicaRenderingStuff);

}