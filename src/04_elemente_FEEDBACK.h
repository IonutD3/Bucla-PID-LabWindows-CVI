/* Calculeaza iesirea regulatorului PID discret. */
double iesire_PID()
{
    double local_yPIDk;
    //Implementare PID, unde: 
		//local_yPIDk este variabila locala calculata la momentul de esantionare tk
		//yPIDk_1, yPIDk_2 sunt variabile globale calculate la momentele anterioare tk_1, tk_2
		//epsk, epsk_1, epsk_2 sunt variabilele globale ale erorii, calculate la momentele anterioare tk, tk_1, tk_2
		//a1,a2,b0,b1,b2 sunt parametrii PID calculati in fct. start_aplicatie()
    local_yPIDk = -a1 * yPIDk_1 - a2 * yPIDk_2 + b0 * epsk + b1 * epsk_1 + b2 * epsk_2;

    return local_yPIDk;
}

/* Calculeaza iesirea procesului discretizat. */
double iesire_Proces()
{
    double local_y_Procesk;
    //Implementare PID, unde: 
		//local_y_Procesk este variabila locala calculata la momentul de esantionare tk
		//y_Procesk_1 este variabila globala calculata la momentul anterior tk_1,
		//u_Procesk_1 este variabila globala calculata la momentul anterior tk_1, 
    local_y_Procesk = y_Procesk_1 + C * (yee - y_Procesk_1);
    yk1 = yk1_1 + C1 * (local_y_Procesk - yk1_1) + C2 * (local_y_Procesk - y_Procesk_1);

    return local_y_Procesk;
}
