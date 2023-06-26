#include "action.hh"

MyActionInitialization::MyActionInitialization()
{}
MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{

//----particle gun----
//  MyGunPrimaryGenerator * genetator = new MyGunPrimaryGenerator();
//  SetUserAction(genetator);

//----GPS----
  SetUserAction(new PrimaryGeneratorAction);

   
  MyrunAction *runAction = new MyrunAction();
  SetUserAction(runAction);
  
  MyEventAction *eventAction = new MyEventAction(runAction);
  SetUserAction(eventAction);
 
  //------ with particle gun generator member variable------- 
  //MyTrackingAction *trackingAction = new MyTrackingAction(genetator);
  //SetUserAction(trackingAction);

  MyTrackingAction *trackingAction = new MyTrackingAction();
  SetUserAction(trackingAction);

  MySteppingAction * steppingAction = new MySteppingAction(eventAction);
  SetUserAction(steppingAction);
}
