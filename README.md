# Bucla PID / PID Control Loop

## 🇷🇴 Română

### Descriere

Acest proiect implementează o **buclă de reglare automată cu regulator PID discret** în C, utilizând **NI LabWindows/CVI** pentru interfața grafică și execuția aplicației.

Aplicația modelează software o buclă de control cu reacție negativă și permite analizarea comportamentului sistemului în timp discret. Algoritmul de control este executat periodic, folosind un timer configurat cu perioada de eșantionare `Te`.

Proiectul este destinat studiului sistemelor de reglare automată și analizei influenței parametrilor PID asupra răspunsului unui proces simulat.

### Funcționalități

- Implementarea unui **regulator PID discret**.
- Configurarea parametrilor:
  - `Kr` — câștigul regulatorului;
  - `Ti` — constanta de timp integrală;
  - `Td` — constanta de timp derivativă;
  - `alpha` — parametrul utilizat pentru filtrarea acțiunii derivative.
- Configurarea **perioadei de eșantionare `Te`**.
- Generarea semnalelor de referință:
  - treaptă;
  - rampă;
  - sinusoidal.
- Comutarea între modurile **Automat** și **Manual**.
- Simularea discretă a unui proces.
- Modelarea elementului de execuție și a traductorului în cadrul buclei simulate.
- Calcularea erorii dintre referință și ieșirea măsurată.
- Calcularea comenzii PID la fiecare perioadă de eșantionare.
- Reprezentarea grafică a semnalului de referință, a răspunsului procesului și a comenzii PID.
- Ștergerea și reluarea graficelor.
- Modificarea parametrilor PID și observarea efectului acestora asupra simulării.

### Structura buclei simulate

```text
Referință
   │
   ▼
[ Generator semnal ]
   │
   ▼
[ Comparator ] ◄──────────────────────────┐
   │                                      │
   │ eroare ε(k)                          │
   ▼                                      │
[ Regulator PID ]                         │
   │                                      │
   │ u(k)                                 │
   ▼                                      │
[ Element de execuție ]                   │
   │                                      │
   ▼                                      │
[ Proces simulat ]                        │
   │                                      │
   ▼                                      │
[ Traductor ] ────────────────────────────┘
```

Calculul este realizat discret, la fiecare eveniment `EVENT_TIMER_TICK`.

### Algoritmul PID

Comanda regulatorului este calculată folosind o ecuație recurentă de forma:

```text
yPID(k) = -a1 · yPID(k-1) -a2 · yPID(k-2) +b0 · ε(k) +b1 · ε(k-1) +b2 · ε(k-2)
```

Coeficienții `a1`, `a2`, `b0`, `b1` și `b2` sunt calculați în funcție de parametrii PID și de perioada de eșantionare.

### Generarea semnalului de referință

Aplicația permite selectarea următoarelor tipuri de semnale.

#### Treaptă

Valoarea de referință este preluată din interfața aplicației.

#### Rampă

Semnalul este calculat în funcție de panta configurată și de timpul de simulare:

```text
r(k) = m · t(k) + r0
```

#### Sinusoidal

Semnalul sinusoidal este generat pe baza amplitudinii și perioadei configurate:

```text
r(k) = A · sin(2π · t(k) / T) + r0
```

### Simularea procesului

Procesul este reprezentat prin ecuații discrete, utilizate pentru simularea evoluției sistemului.

Modelul conține și componente intermediare asociate elementului de execuție și traductorului, astfel încât să poată fi analizată o buclă de feedback completă la nivel de simulare.

### Interfața grafică

Interfața este realizată folosind **LabWindows/CVI User Interface Resource (`.uir`)**.

Aceasta permite:

- pornirea simulării;
- oprirea aplicației;
- ștergerea graficelor;
- selectarea regimului Automat/Manual;
- selectarea tipului semnalului de referință;
- configurarea parametrilor semnalului;
- configurarea parametrilor PID;
- configurarea perioadei de eșantionare;
- vizualizarea evoluției semnalelor simulate.

### Structura proiectului

```text
Bucla-PID–LabWindows-CVI/
│
├── src/
│   ├── bucla_PID.c
│   ├── bucla_PID.h
│   ├── 00_Declaratii_Variabile_S.h
│   ├── 01_Functionare_A_M_S.h
│   ├── 02_Functii_Utilitare_S.h
│   ├── 03_Generare_Semnale_S.h
│   └── 04_elemente_FEEDBACK
│
├── ui/
│   └── bucla_PID.uir
│
└── README.md
```

### Fișiere principale
`bucla_PID.c`

Conține logica principală a aplicației:

- inițializarea interfeței;
- pornirea aplicației;
- configurarea timerului;
- eșantionarea sistemului;
- calcularea erorii;
- calcularea comenzii PID;
- simularea procesului;
- actualizarea variabilelor de stare;
- reprezentarea grafică a rezultatelor.

`bucla_PID.h`

Fișier generat de LabWindows/CVI pentru identificarea panoului și controalelor definite în interfața `.uir`.

`bucla_PID.uir`

Resursa grafică a interfeței utilizată de LabWindows/CVI.

`00_Declaratii_Variabile_S.h`

Conține declarațiile variabilelor utilizate pentru semnale, eșantionare, proces, regulator PID și elementele buclei simulate.

`01_Functionare_A_M_S.h`

Conține logica pentru funcționarea în regim Automat/Manual.

`02_Functii_Utilitare_S.h`

Conține funcții auxiliare pentru operațiile de interfață și recalcularea parametrilor necesari regulatorului.

`03_Generare_Semnale_S.h`

Conține funcțiile pentru generarea semnalelor de referință de tip treaptă, rampă și sinus.

`04_elemente_FEEDBACK.h`

Conține implementarea regulatorului PID și a elementelor procesului utilizate în simularea buclei de feedback.

### Tehnologii utilizate

- **C**
- **NI LabWindows/CVI**
- **CVI User Interface Resource (.uir)**
- control în timp discret
- regulator PID
- simularea unui proces dinamic
- sisteme de reglare cu feedback

### Rulare

Pentru compilarea și rularea proiectului este necesar NI LabWindows/CVI.

Pașii generali:

1. Deschide proiectul în LabWindows/CVI.
2. Verifică existența fișierelor `.c`, `.h` și `.uir`.
3. Compilează aplicația.
4. Rulează programul.
5. Configurează perioada de eșantionare și parametrii PID.
6. Selectează tipul semnalului de referință.
7. Pornește simularea.
8. Analizează grafic răspunsul procesului simulat și comanda regulatorului.

### Scop educațional

Proiectul poate fi utilizat pentru:

- înțelegerea funcționării unui regulator PID;
- studierea sistemelor de control în timp discret;
- observarea influenței parametrilor `Kr`, `Ti` și `Td`;
- studiul influenței perioadei de eșantionare;
- analiza răspunsului unui proces simulat la semnale de tip treaptă, rampă și sinus;
- familiarizarea cu dezvoltarea aplicațiilor de simulare și control în LabWindows/CVI.

---

## 🇬🇧 English

This project implements and simulates a **closed-loop automatic control system using a discrete PID controller**, developed in **NI LabWindows/CVI**.

The application models a feedback control loop in software and allows the system behavior to be analyzed in discrete time. The control algorithm is executed periodically using a timer configured with the sampling period `Te`.

The project is intended for studying automatic control systems and analyzing the influence of PID parameters on the response of a simulated process.

### Features

- **Discrete PID controller** implementation.
- Configuration of:
  - `Kr` — controller gain;
  - `Ti` — integral time constant;
  - `Td` — derivative time constant;
  - `alpha` — parameter used for derivative filtering.
- Configurable **sampling period `Te`**.
- Reference signal generation:
  - step;
  - ramp;
  - sinusoidal.
- **Automatic/Manual** operating modes.
- Discrete simulation of a process.
- Simulation of actuator and transducer elements within the feedback loop.
- Control error calculation.
- PID control output calculation at each sampling instant.
- Graphical visualization of the reference signal, process response and PID output.
- Graph reset functionality.
- PID parameter adjustment and observation of its effect on the simulation.

### Simulated Control Loop

```text
Reference
   │
   ▼
[ Signal Generator ]
   │
   ▼
[ Comparator ] ◄──────────────────────────┐
   │                                      │
   │ error ε(k)                           │
   ▼                                      │
[ PID Controller ]                        │
   │                                      │
   │ u(k)                                 │
   ▼                                      │
[ Actuator ]                              │
   │                                      │
   ▼                                      │
[ Simulated Process ]                     │
   │                                      │
   ▼                                      │
[ Transducer ] ───────────────────────────┘
```

The calculations are performed in discrete time at every `EVENT_TIMER_TICK`.

### PID Algorithm

The controller output is calculated using a recursive discrete equation:

```text
yPID(k) = -a1 · yPID(k-1) -a2 · yPID(k-2) +b0 · ε(k) +b1 · ε(k-1) +b2 · ε(k-2)
```

The coefficients `a1`, `a2`, `b0`, `b1` and `b2` are calculated according to the PID parameters and the selected sampling period.

### Reference Signal Generation

The application supports three reference signal types.

#### Step

The reference value is read from the application interface.

#### Ramp

The ramp signal is calculated according to the configured slope and simulation time:

```text
r(k) = m · t(k) + r0
```
#### Sinusoidal

The sinusoidal signal is generated using the configured amplitude and period:

```text
r(k) = A · sin(2π · t(k) / T) + r0
```
### Process Simulation

The process is represented using discrete equations that simulate the evolution of the system.

The model also includes intermediate elements associated with the actuator and transducer, allowing a complete feedback loop to be analyzed at simulation level.

### Graphical User Interface

The graphical interface is implemented using **LabWindows/CVI User Interface Resource (`.uir`)**.

It provides controls for:

- starting the simulation;
- exiting the application;
- clearing graphs;
- selecting Automatic/Manual mode;
- selecting the reference signal;
- configuring signal parameters;
- configuring PID parameters;
- configuring the sampling period;
- visualizing simulated signals.

### Project structure

```text
Bucla-PID–LabWindows-CVI/
│
├── src/
│   ├── bucla_PID.c
│   ├── bucla_PID.h
│   ├── 00_Declaratii_Variabile_S.h
│   ├── 01_Functionare_A_M_S.h
│   ├── 02_Functii_Utilitare_S.h
│   ├── 03_Generare_Semnale_S.h
│   └── 04_elemente_FEEDBACK
│
├── ui/
│   └── bucla_PID.uir
│
└── README.md
```

### Main Files
`bucla_PID.c`

Contains the main application logic:

- interface initialization;
- application startup;
- timer configuration;
- system sampling;
- error calculation;
- PID calculation;
- process simulation;
- state variable updates;
- graphical visualization.

`bucla_PID.h`

Header generated by LabWindows/CVI for identifying the panel and controls defined in the `.uir` interface.

`bucla_PID.uir`

Graphical user interface resource used by LabWindows/CVI.

`00_Declaratii_Variabile_S.h`

Contains variable declarations used for signals, sampling, process simulation, PID control and feedback-loop elements.

`01_Functionare_A_M_S.h`

Contains the logic for Automatic/Manual operation.

`02_Functii_Utilitare_S.h`

Contains utility functions for interface operations and recalculation of parameters required by the controller.

`03_Generare_Semnale_S.h`

Contains functions for generating step, ramp and sinusoidal reference signals.

`04_elemente_FEEDBACK.h`

Contains the PID controller implementation and the process elements used in the simulated feedback loop.

### Technologies

- **C**
- **NI LabWindows/CVI**
- **CVI User Interface Resource (.uir)**
- discrete-time control
- PID controller
- dynamic process simulation
- feedback control systems

### Running the Project

The project requires NI LabWindows/CVI to compile and run.

General steps:

1. Open the project in LabWindows/CVI.
2. Verify that the `.c`, `.h` and `.uir` files are available.
3. Compile the application.
4. Run the program.
5. Configure the sampling period and PID parameters.
6. Select the desired reference signal.
7. Start the simulation.
8. Analyze the simulated process response and controller output.

### Educational Purpose

This project can be used to study:

- PID controller operation;
- discrete-time control systems;
- the influence of `Kr`, `Ti` and `Td`;
- the influence of the sampling period;
- the response of a simulated process to step, ramp and sinusoidal signals;
- development of control and simulation applications using LabWindows/CVI.

---

## 👤 Autor / Author

**IonutD**
