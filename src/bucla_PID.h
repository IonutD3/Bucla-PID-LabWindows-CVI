/**************************************************************************/
/* Fisier de includere generat de LabWindows/CVI pentru resursa UIR              */
/*                                                                        */
/* ATENTIE: Continutul acestui fisier este generat automat. Nu il modifica manual.  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panouri si controale. */

#define  PANEL                            1
#define  PANEL_OKBUTTON_2                 2       /* tip: comanda; callback: stergere_grafice */
#define  PANEL_OKBUTTON                   3       /* tip: comanda; callback: start_aplicatie */
#define  PANEL_QUITBUTTON                 4       /* tip: comanda; callback: QuitCallback */
#define  PANEL_TEXTBOX                    5       /* tip: caseta de text */
#define  PANEL_LED                        6       /* tip: LED */
#define  PANEL_BINARYSWITCH               7       /* tip: comutator binar */
#define  PANEL_BINARYSWITCH_2             8       /* tip: comutator binar */
#define  PANEL_COMANDA                    9       /* tip: grafic */
#define  PANEL_GRAPH                      10      /* tip: grafic */
#define  PANEL_SEL_REF                    11      /* tip: glisor; callback: selectie_semnal */
#define  PANEL_REFERINTA                  12      /* tip: scala */
#define  PANEL_T_SINUS                    13      /* tip: numeric; callback: detectare_comutare_SIN */
#define  PANEL_A_SINUS                    14      /* tip: numeric; callback: detectare_comutare_SIN */
#define  PANEL_M_PANTA                    15      /* tip: numeric; callback: modificare_Panta */
#define  PANEL_TIMER                      16      /* tip: temporizator; callback: esantionare */
#define  PANEL_DECORATION                 17      /* tip: decor */
#define  PANEL_DECORATION_3               18      /* tip: decor */
#define  PANEL_TEXTMSG_2                  19      /* tip: mesaj text */
#define  PANEL_TEXTMSG                    20      /* tip: mesaj text */
#define  PANEL_TI                         21      /* tip: numeric; callback: modificare_PM_PID */
#define  PANEL_TD                         22      /* tip: numeric; callback: modificare_PM_PID */
#define  PANEL_KR                         23      /* tip: numeric; callback: modificare_PM_PID */
#define  PANEL_TE                         24      /* tip: numeric; callback: setare_TE */
#define  PANEL_ALPHA                      25      /* tip: numeric; callback: modificare_PM_PID */


     /* Tablouri de controale. */

          /* Nu exista tablouri de controale. */


     /* Bare de meniu si elemente de meniu. */

          /* Nu exista bare de meniu. */


     /* Prototipurile functiilor callback. */

int  CVICALLBACK detectare_comutare_SIN(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK esantionare(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modificare_Panta(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK modificare_PM_PID(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK QuitCallback(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK selectie_semnal(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK setare_TE(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_aplicatie(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK stergere_grafice(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif