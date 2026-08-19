/* Declaratii pentru starea aplicatiei si pentru algoritmul de reglare. */

static int panelHandle;

/* Starea regimului manual sau automat. */
int regim;
int stare_led;
int valoare_led;

/* Variabile pentru generarea semnalelor de referinta. */
double Refk, Refk_1, Refk_2, Refk0;
int sel_ref;
double timp_rampa_tk, timp_sinus_tk;
double T_sin, A_sin;
int comutare_Sin;

/* Perioada si momentele de esantionare. */
double Te, T1, T2, C1, C2, yk1, yk1_1;
double tk_1, tk;

/* Parametrii elementului de executie. */
double Tee, Cee, T1ee, T2ee, C1ee, C2ee, yee, yee_1, yee1, yee1_1;

/* Parametrii traductorului. */
double Ttr, Ctr, T1tr, T2tr, C1tr, C2tr, ytr, ytr_1;

/* Variabilele procesului. */
double y_Procesk_1, y_Procesk;
double u_Procesk_1, u_Procesk;
double C, T;

/* Variabilele regulatorului PID. */
double epsk_2, epsk_1, epsk;
double yPIDk_2, yPIDk_1, yPIDk;
double alpha, Kr, Ti, Td;
double p0, p1, p2, q0, q1, q2;
double a1, a2, b0, b1, b2;
