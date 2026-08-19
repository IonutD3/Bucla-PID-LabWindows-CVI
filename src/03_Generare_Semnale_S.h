/* Genereaza semnale de referinta de tip treapta, rampa sau sinus. */
double generare_semnal()
{
    double local_Refk;
    double local_m, local_n;

    local_Refk = 0;

    switch (sel_ref)
    {
        case 0:
            /* Afiseaza controlul pentru treapta si ascunde celelalte controale. */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 0);

            GetCtrlVal(panelHandle, PANEL_REFERINTA, &local_Refk);
            break;

        case 1:
            /* Afiseaza controlul pentru panta rampei. */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 0);

            GetCtrlVal(panelHandle, PANEL_M_PANTA, &local_m);
            local_n = Refk0;
            local_Refk = local_m * timp_rampa_tk + local_n;
            timp_rampa_tk = timp_rampa_tk + Te;
            break;

        case 2:
            /* Afiseaza controalele pentru amplitudinea si perioada sinusului. */
            SetCtrlAttribute(panelHandle, PANEL_REFERINTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_M_PANTA, ATTR_VISIBLE, 0);
            SetCtrlAttribute(panelHandle, PANEL_A_SINUS, ATTR_VISIBLE, 1);
            SetCtrlAttribute(panelHandle, PANEL_T_SINUS, ATTR_VISIBLE, 1);

            if (comutare_Sin == 0)
            {
                GetCtrlVal(panelHandle, PANEL_A_SINUS, &A_sin);
                GetCtrlVal(panelHandle, PANEL_T_SINUS, &T_sin);
            }
            else
            {
                /* Comutarea sinusului se face la trecerea prin valoarea de referinta initiala. */
                if ((Refk_2 < Refk0) && (Refk_1 >= Refk0))
                {
                    comutare_Sin = 0;
                    timp_sinus_tk = 2 * Te;
                }

                if ((Refk_2 > Refk0) && (Refk_1 <= Refk0))
                {
                    comutare_Sin = 0;
                    timp_sinus_tk = 2 * Te + T_sin / 2;
                }
            }

            local_Refk = A_sin * sin(((2 * Pi()) / T_sin) * timp_sinus_tk) + Refk0;
            timp_sinus_tk = timp_sinus_tk + Te;
            break;

        default:
            break;
    }

    return local_Refk;
}

/* Proceseaza selectarea tipului de semnal de referinta. */
int CVICALLBACK selectie_semnal(int panel, int control, int event,
                                 void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            GetCtrlVal(panelHandle, PANEL_SEL_REF, &sel_ref);

            switch (sel_ref)
            {
                case 0:
                    break;

                case 1:
                    /* La schimbarea pe rampa, pornirea se face din valoarea curenta. */
                    timp_rampa_tk = 0;
                    Refk0 = Refk;
                    break;

                case 2:
                    /* La schimbarea pe sinus, faza este initializata din valoarea curenta. */
                    timp_sinus_tk = 0;
                    Refk0 = Refk;
                    break;

                default:
                    break;
            }
            break;
    }

    return 0;
}

/* Reinitializeaza rampa atunci cand se modifica panta. */
int CVICALLBACK modificare_Panta(int panel, int control, int event,
                                  void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            timp_rampa_tk = 0;
            Refk0 = Refk;
            break;
    }

    return 0;
}

/* Solicita o comutare controlata intre doua configuratii de sinus. */
int CVICALLBACK detectare_comutare_SIN(int panel, int control, int event,
                                       void *callbackData, int eventData1, int eventData2)
{
    switch (event)
    {
        case EVENT_COMMIT:
            comutare_Sin = 1;
            break;
    }

    return 0;
}
