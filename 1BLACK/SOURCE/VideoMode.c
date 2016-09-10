uint8 SetVideoMode()
 {
 int WhichVideoCable;

 WhichVideoCable = vid_check_cable();

 if(WhichVideoCable == CT_VGA) vid_set_mode(DM_640x480_VGA, PM_RGB565);
 else{ 
 if(flashrom_get_region() == FLASHROM_REGION_EUROPE){
 if(!HertzSelectScreen()) return(0);
 }
 else vid_set_mode(DM_640x480_NTSC_IL, PM_RGB565);
 }

 return(1);
 }
 