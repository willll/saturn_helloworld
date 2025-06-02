#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>
#include	<machine.h>

#define		_SPR2_
#include        "sega_spr.h"
#include        "sega_scl.h"
#include        "sega_dbg.h"
#include        "sega_per.h"

#include	"v_blank/v_blank.h"

#define   DISP_XSIZE       320
#define   DISP_YSIZE       224


int main()
{
    SCL_Vdp2Init();
    SetVblank();
    set_imask(0);

    SCL_SetPriority(SCL_SP0|SCL_SP1|SCL_SP2|SCL_SP3|
                    SCL_SP4|SCL_SP5|SCL_SP6|SCL_SP7,6);
    SCL_SetSpriteMode(SCL_TYPE1,SCL_MIX,SCL_SP_WINDOW);


    SPR_SetEraseData(RGB16_COLOR(0,0,0),0,0,DISP_XSIZE-1,DISP_YSIZE-1);
    SCL_SetFrameInterval(1);
    DBG_Initial(&PadData1,RGB16_COLOR(31,31,31),0);

    DBG_ClearScreen();
    DBG_DisplayOn();
    DBG_Printf("Hello World !\n");

    for(int i = 0;; i++) {
        if (PadData1 & PAD_S) {
            DBG_Printf("Exit !\n");
            break;
        }
    }

    return 0;
}
