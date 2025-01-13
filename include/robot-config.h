using namespace vex;

extern brain Brain;

//To set up a motor called LeftFront here, you'd use
//extern motor LeftFront;
extern controller Controller;
//Add your devices below, and don't forget to do the same in robot-config.cpp:
extern motor LB;
extern motor LM;
extern motor LF;
extern motor RB;
extern motor RM;
extern motor RF;
extern motor intakeL;
extern motor intakeR;
extern motor wallL;
extern motor wallR;
extern motor_group intake;

// Sensors
extern digital_out Clamp;
extern digital_out Claw;
extern digital_out Doink;
extern inertial Gyro;
extern rotation Wall;
extern vision Rings;

void  vexcodeInit( void );