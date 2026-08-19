/* Functii utilitare pentru interfata aplicatiei. */

/* Sterge trasarile de pe grafice si reseteaza timpul de esantionare. */
int CVICALLBACK stergere_grafice(int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            DeleteGraphPlot(panelHandle, PANEL_GRAPH, -1, VAL_IMMEDIATE_DRAW);
            DeleteGraphPlot(panelHandle, PANEL_COMANDA, -1, VAL_IMMEDIATE_DRAW);
            tk_1 = 0;
            tk = 0;
            break;
    }

    return 0;
}

/* Inchide interfata grafica si opreste aplicatia. */
int CVICALLBACK QuitCallback(int panel, int control, int event,
                             void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            QuitUserInterface(0);
            break;
    }

    return 0;
}

/* Recalculeaza coeficientii regulatorului PID dupa modificarea parametrilor. */
int CVICALLBACK modificare_PM_PID(int panel, int control, int event,
                                  void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
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
            break;
    }

    return 0;
}
