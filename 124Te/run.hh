#ifndef RUN_HH
#define RUN_HH
#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "g4root.hh"

class MyrunAction : public G4UserRunAction
{
 public: 
 MyrunAction();
 ~MyrunAction();

  virtual void BeginOfRunAction(const G4Run*);
  virtual void EndOfRunAction(const G4Run*);    

  void PlusOneMinusCaptureInRun();
  void PlusOneMinusCaptureInRunInScintillator();
  void PlusOneMinusCaptureInRunInTarget();
  void PlusOneMinusCaptureInRunInWorld();







  private:
  int fMuMinusCaptures;
  int fMuMinusCapturesInScintillator;
  int fMuMinusCapturesInTarget;
  int fMuMinusCapturesInWorld;
//  int fMuMinusCapturesInRealTarget;


};

#endif