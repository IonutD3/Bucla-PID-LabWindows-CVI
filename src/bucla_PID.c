#include "toolbox.h"
#include <ansi_c.h>
#include <cvirte.h>
#include <userint.h>
#include "bucla_PID.h"

#include "00_Declaratii_Variabile_S.h"
#include "01_Functionare_A_M_S.h"
#include "02_Functii_Utilitare_S.h"
#include "03_Generare_Semnale_S.h"
#include "04_elemente_FEEDBACK.h"

int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                      LPSTR lpszCmdLine, int nCmdShow)
{
    if (InitCVIRTE(hInstance, 0, 0) == 0)
        return -1;

    if ((panelHandle = LoadPanel(0, "bucla_PID.uir", PANEL)) < 0)
        return -1;

    DisplayPanel(panelHandle);
    RunUserInterface();
    DiscardPanel(panelHandle);

    return 0;
}

/* Initializeaza aplicatia si porneste temporizatorul de esantionare. */
int CVICALLBACK start_aplicatie(int panel, int control, int event,
                                void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            InsertTextBoxLine(panelHandle, PANEL_TEXTBOX, -1,
                              "Aplicatia a fost pornita cu succes.");

            GetCtrlVal(panelHandle, PANEL_TE, &Te);
            tk_1 = 0;
            tk = Te;

            Refk = 0;
            Refk_1 = 0;
            Refk_2 = 0;
            sel_ref = 0;

            comutare_Sin = 0;
            GetCtrlVal(panelHandle, PANEL_A_SINUS, &A_sin);
            GetCtrlVal(panelHandle, PANEL_T_SINUS, &T_sin);

            GetCtrlVal(panelHandle, PANEL_KR, &Kr);
            GetCtrlVal(panelHandle, PANEL_TI, &Ti);
            GetCtrlVal(panelHandle, PANEL_TD, &Td);
            GetCtrlVal(panelHandle, PANEL_ALPHA, &alpha);

            p0 = Kr * ((4 / (Te * Te)) * (alpha * Td * Ti + Ti * Td) + (2 / Te) * (Ti + alpha * Td) + 1);
            p1 = Kr * (-(8 / (Te * Te)) * (alpha * Td * Ti + Td * Ti) + 2);
            p2 = Kr * ((4 / (Te * Te)) * (alpha * Td * Ti + Ti * Td) - (2 / Te) * (Ti + alpha * Td) + 1);

            q0 = (4 / (Te * Te)) * Ti * alpha * Td + (2 / Te) * Ti;
            q1 = -(8 / (Te * Te)) * Ti * alpha * Td;
            q2 = (4 / (Te * Te)) * Ti * alpha * Td - (2 / Te) * Ti;

            a1 = q1 / q0;
            a2 = q2 / q0;
            b0 = p0 / q0;
            b1 = p1 / q0;
            b2 = p2 / q0;

            /* Parametrii procesului sunt obtinuti prin discretizarea modelului continuu. */
            T = 0.02;
            //T = 0.2;
            T1 = 3.2;
            //T1 = 32;
            T2 = 7.9;
            //T2 = 79;

            C = Te / (Te + T);
            C1 = Te / (Te + T2);
            C2 = T1 / (Te + T2);

            //Tee = 0.04;
            //Cee = Te / (Te + Tee);
            T1ee = 0.64;
            //T1ee = 6.4;
            T2ee = 1.58;
            //T2ee = 15.8;
            C1ee = Te / (Te + T2ee);
            C2ee = T1ee / (Te + T2ee);

            Ttr = 0.79;
            //Ttr = 7.9;
            Ctr = Te / (Te + Ttr);
	    //T1tr = 3.2;
	    //T2tr = 7.9;
	    //C1tr = Te / (Te + T2tr);
	    //C2tr = T1tr / (Te + T2tr);
			
	    //yee1_1 = 0;
	    //ytr_1 = 0;

            /* Dezactiveaza butonul de pornire dupa initializarea aplicatiei. */
            SetCtrlAttribute(panelHandle, PANEL_OKBUTTON, ATTR_DIMMED, 1);

            /* Configureaza si porneste temporizatorul de esantionare. */
            SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_INTERVAL, Te);
            SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_ENABLED, 1);
            break;
    }

    return 0;
}

/* Executa algoritmul de reglare la fiecare impuls al temporizatorului. */
int CVICALLBACK esantionare(int panel, int control, int event,
                            void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_TIMER_TICK:
            /* Actualizeaza regimul manual sau automat. */
            functiune_Automat_Manual();

            /* Genereaza semnalul de referinta ales de utilizator. */
            Refk = generare_semnal();

            /* Calculeaza eroarea fata de iesirea traductorului. */
            //epsk=Refk-y_Procesk_1;
            epsk = Refk - ytr_1;

            /* Calculeaza comanda regulatorului PID. */
            yPIDk = iesire_PID();

            /* Aplicarea comenzii asupra elementului de executie. */
            u_Procesk = yPIDk;
            yee = yPIDk;
            yee1 = yee1_1 + C1ee * (yee - yee1_1) + C2ee * (yee - yee_1);

            /* Calculeaza iesirea procesului discretizat. */
            y_Procesk = iesire_Proces();

            /* Modeleaza raspunsul traductorului. */
            ytr = ytr_1 + Ctr * (yk1 - ytr_1);

            /* Afiseaza referinta si raspunsul procesului. */
            PlotLine(panelHandle, PANEL_GRAPH, tk_1, Refk_1, tk, Refk, VAL_GREEN);
            PlotLine(panelHandle, PANEL_GRAPH, tk_1, yk1_1, tk, yk1, VAL_RED);

            /* Afiseaza semnalul de comanda al regulatorului PID. */
            PlotLine(panelHandle, PANEL_COMANDA, tk_1, yPIDk_1, tk, yPIDk, VAL_BLUE);

            /* Actualizeaza valorile necesare urmatorului pas de esantionare. */
            tk_1 = tk;
            tk = tk + Te;

            Refk_2 = Refk_1;
            Refk_1 = Refk;

            epsk_2 = epsk_1;
            epsk_1 = epsk;

            yPIDk_2 = yPIDk_1;
            yPIDk_1 = yPIDk;

            u_Procesk_1 = u_Procesk;
            y_Procesk_1 = y_Procesk;

            yk1_1 = yk1;
            ytr_1 = ytr;
            yee_1 = yee;
            yee1_1 = yee1;
            break;
    }

    return 0;
}

/* Actualizeaza perioada de esantionare din interfata grafica. */
int CVICALLBACK setare_TE(int panel, int control, int event,
                          void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            GetCtrlVal(panelHandle, PANEL_TE, &Te);
            SetCtrlAttribute(panelHandle, PANEL_TIMER, ATTR_INTERVAL, Te);
            break;
    }

    return 0;
}
