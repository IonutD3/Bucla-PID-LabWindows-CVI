/* Gestioneaza comutarea intre regimul manual si automat. */
int functiune_Automat_Manual()
{
    GetCtrlVal(panelHandle, PANEL_BINARYSWITCH, &regim);

    if (regim)
    {
        /* In regim manual, comutatorul LED este disponibil utilizatorului. */
        SetCtrlAttribute(panelHandle, PANEL_BINARYSWITCH_2, ATTR_DIMMED, 0);
        GetCtrlVal(panelHandle, PANEL_BINARYSWITCH_2, &stare_led);
        SetCtrlVal(panelHandle, PANEL_LED, stare_led);
    }
    else
    {
        /* In regim automat, LED-ul este comutat periodic de aplicatie. */
        SetCtrlAttribute(panelHandle, PANEL_BINARYSWITCH_2, ATTR_DIMMED, 1);

        GetCtrlVal(panelHandle, PANEL_LED, &valoare_led);
        if (valoare_led == 0)
        {
            SetCtrlVal(panelHandle, PANEL_LED, 1);
        }
        else
        {
            SetCtrlVal(panelHandle, PANEL_LED, 0);
        }
    }

    return 0;
}
