
////////////////////////////////////////////////////////////////////////
//                                                                    //
//   Software Name: DANCE Data Acquisition and Analysis Package       //
//     Subpackage: DANCE_Simulation_G4.9                              //
//   Identifying Number: C18105                                       // 
//                                                                    //
////////////////////////////////////////////////////////////////////////
//                                                                    //
//                                                                    //
// Copyright 2019.                                                    //
// Triad National Security, LLC. All rights reserved.                 //
//                                                                    //
//                                                                    //
//                                                                    //
// This program was produced under U.S. Government contract           //
// 89233218CNA000001 for Los Alamos National Laboratory               //
// (LANL), which is operated by Triad National Security, LLC          //
// for the U.S. Department of Energy/National Nuclear Security        //
// Administration. All rights in the program are reserved by          //
// Triad National Security, LLC, and the U.S. Department of           //
// Energy/National Nuclear Security Administration. The Government    //
// is granted for itself and others acting on its behalf a            //
// nonexclusive, paid-up, irrevocable worldwide license in this       //
// material to reproduce, prepare derivative works, distribute        //
// copies to the public, perform publicly and display publicly,       //
// and to permit others to do so.                                     //
//                                                                    //
// This is open source software; you can redistribute it and/or       //
// modify it under the terms of the GPLv2 License. If software        //
// is modified to produce derivative works, such modified             //
// software should be clearly marked, so as not to confuse it         //
// with the version available from LANL. Full text of the GPLv2       //
// License can be found in the License file of the repository         //
// (GPLv2.0_License.txt).                                             //
//                                                                    //
////////////////////////////////////////////////////////////////////////

#include "DANCEHadronPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>   


DANCEHadronPhysics::DANCEHadronPhysics(const G4String& name)
                   :  G4VPhysicsConstructor(name)
{
}

DANCEHadronPhysics::~DANCEHadronPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4ProcessManager.hh"
#include "G4NeutronInelasticCrossSection.hh"

#include "G4ExcitationHandler.hh"
#include "G4Evaporation.hh"

void DANCEHadronPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;

  G4Evaporation * theEvaporation = new G4Evaporation;
  G4ExcitationHandler * theHandler = new G4ExcitationHandler;
  theHandler->SetEvaporation(theEvaporation);

   // Pi+ Physics
   pManager = G4PionPlus::PionPlus()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* theppElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theppElasticModel = new G4HadronElastic();
   theppElasticProcess->RegisterMe(theppElasticModel);
   pManager->AddDiscreteProcess(theppElasticProcess);
 
   G4PionPlusInelasticProcess* thePionPlusInelasticProcess 
                         = new G4PionPlusInelasticProcess(); 

/*
   G4PionPlusInelasticProcess* thePionPlusLEPModel = new G4PionPlusInelasticProcess();
   G4PionPlusInelasticProcess* thePionPlusHEPModel = new G4PionPlusInelasticProcess();
   thePionPlusInelasticProcess->RegisterMe(thePionPlusLEPModel);
   thePionPlusInelasticProcess->RegisterMe(thePionPlusHEPModel);
*/
   pManager->AddDiscreteProcess(thePionPlusInelasticProcess);


   G4VProcess* theppMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theppIonisation        = new G4hIonisation();
   // 
   pManager->AddProcess(theppIonisation);
   pManager->AddProcess(theppMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theppMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theppIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theppMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theppIonisation,        idxPostStep,2);


   // Pi- Physics
   pManager = G4PionMinus::PionMinus()->GetProcessManager();

   G4HadronElasticProcess* thepmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thepmElasticModel = new G4HadronElastic();
   thepmElasticProcess->RegisterMe(thepmElasticModel);
   pManager->AddDiscreteProcess(thepmElasticProcess);

   G4PionMinusInelasticProcess* thePionMinusInelasticProcess 
                         = new G4PionMinusInelasticProcess(); 

/*
   G4PionMinusInelasticProcess* thePionMinusLEPModel = new G4PionMinusInelasticProcess();
   G4PionMinusInelasticProcess* thePionMinusHEPModel = new G4PionMinusInelasticProcess();  
   thePionMinusInelasticProcess->RegisterMe(thePionMinusLEPModel);
   thePionMinusInelasticProcess->RegisterMe(thePionMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(thePionMinusInelasticProcess);

   G4VProcess* thepmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thepmIonisation        = new G4hIonisation();
   // 
   // add processes
   pManager->AddProcess(thepmIonisation);
   pManager->AddProcess(thepmMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thepmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thepmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thepmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thepmIonisation,        idxPostStep,2);


   // K+ Physics
   pManager = G4KaonPlus::KaonPlus()->GetProcessManager();

   G4HadronElasticProcess* thekpElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thekpElasticModel = new G4HadronElastic();
   thekpElasticProcess->RegisterMe(thekpElasticModel);
   pManager->AddDiscreteProcess(thekpElasticProcess);

   G4KaonPlusInelasticProcess* theKaonPlusInelasticProcess 
                         = new G4KaonPlusInelasticProcess(); 

/*
   G4KaonPlusInelasticProcess* theKaonPlusLEPModel = new G4KaonPlusInelasticProcess();
   G4KaonPlusInelasticProcess* theKaonPlusHEPModel = new G4KaonPlusInelasticProcess();
   theKaonPlusInelasticProcess->RegisterMe(theKaonPlusLEPModel);
   theKaonPlusInelasticProcess->RegisterMe(theKaonPlusHEPModel);
*/  
   pManager->AddDiscreteProcess(theKaonPlusInelasticProcess);

   G4VProcess* thekpMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thekpIonisation        = new G4hIonisation();
   // 
   // add processes
   pManager->AddProcess(thekpIonisation);
   pManager->AddProcess(thekpMultipleScattering);
   // 
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thekpMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thekpIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thekpMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thekpIonisation,        idxPostStep,2);


   // K- Physics
   pManager = G4KaonMinus::KaonMinus()->GetProcessManager();

   // add processes
   G4HadronElasticProcess* thekmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thekmElasticModel = new G4HadronElastic();
   thekmElasticProcess->RegisterMe(thekmElasticModel);
   pManager->AddDiscreteProcess(thekmElasticProcess);

   G4KaonMinusInelasticProcess* theKaonMinusInelasticProcess 
                         = new G4KaonMinusInelasticProcess(); 
/*
   G4KaonMinusInelasticProcess* theKaonMinusLEPModel = new G4KaonMinusInelasticProcess();
   G4KaonMinusInelasticProcess* theKaonMinusHEPModel = new G4KaonMinusInelasticProcess();
   theKaonMinusInelasticProcess->RegisterMe(theKaonMinusLEPModel);
   theKaonMinusInelasticProcess->RegisterMe(theKaonMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theKaonMinusInelasticProcess);

   G4VProcess* thekmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thekmIonisation        = new G4hIonisation();

   pManager->AddProcess(thekmIonisation);
   pManager->AddProcess(thekmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thekmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thekmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thekmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thekmIonisation,        idxPostStep,2);


   // Kaon0L Phsics
   pManager = G4KaonZeroLong::KaonZeroLong()->GetProcessManager();

   G4HadronElasticProcess* thek0lElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thek0lElasticModel = new G4HadronElastic();
   thek0lElasticProcess->RegisterMe(thek0lElasticModel);
   pManager->AddDiscreteProcess(thek0lElasticProcess);

   G4KaonZeroLInelasticProcess* theKaonZeroLInelasticProcess 
                         = new G4KaonZeroLInelasticProcess(); 
/*
   G4KaonZeroLInelasticProcess* theKaonZeroLLEPModel = new G4KaonZeroLInelasticProcess();
   G4KaonZeroLInelasticProcess* theKaonZerolHEPModel = new G4KaonZeroLInelasticProcess();
   theKaonZeroLInelasticProcess->RegisterMe(theKaonZeroLLEPModel);
   theKaonZeroLInelasticProcess->RegisterMe(theKaonZerolHEPModel);
*/  
   pManager->AddDiscreteProcess(theKaonZeroLInelasticProcess);


   // Kaon0S Phsics
   pManager = G4KaonZeroShort::KaonZeroShort()->GetProcessManager();

   G4HadronElasticProcess* thek0sElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thek0sElasticModel = new G4HadronElastic();
   thek0sElasticProcess->RegisterMe(thek0sElasticModel);
   pManager->AddDiscreteProcess(thek0sElasticProcess);

   G4KaonZeroSInelasticProcess* theKaonZeroSInelasticProcess 
                         = new G4KaonZeroSInelasticProcess(); 

/*
   G4KaonZeroSInelastic* theKaonZeroSLEPModel = new G4KaonZeroSInelasticProcess();
   G4KaonZeroSInelastic* theKaonZerosHEPModel = new G4KaonZeroSInelasticProcess();
   theKaonZeroSInelasticProcess->RegisterMe(theKaonZeroSLEPModel);
   theKaonZeroSInelasticProcess->RegisterMe(theKaonZerosHEPModel);
*/  
  
   pManager->AddDiscreteProcess(theKaonZeroSInelasticProcess);


   // Proton Physics
   pManager = G4Proton::Proton()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thepElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thepElasticModel = new G4HadronElastic();
   thepElasticProcess->RegisterMe(thepElasticModel);
   pManager->AddDiscreteProcess(thepElasticProcess);

   G4ProtonInelasticProcess* theProtonInelasticProcess 
                         = new G4ProtonInelasticProcess(); 

/*
   G4ProtonInelasticProcess* theProtonLEPModel = new G4ProtonInelasticProcess();
   G4ProtonInelasticProcess* theProtonHEPModel = new G4ProtonInelasticProcess();
   theProtonInelasticProcess->RegisterMe(theProtonLEPModel);
   theProtonInelasticProcess->RegisterMe(theProtonHEPModel);
*/  
   pManager->AddDiscreteProcess(theProtonInelasticProcess);

   G4VProcess* thepMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thepIonisation        = new G4hIonisation();

   pManager->AddProcess(thepIonisation);
   pManager->AddProcess(thepMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thepMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thepIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thepMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thepIonisation,        idxPostStep,2);


   // anti-proton Physics
   pManager = G4AntiProton::AntiProton()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theapElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theapElasticModel = new G4HadronElastic();
   theapElasticProcess->RegisterMe(theapElasticModel);
   pManager->AddDiscreteProcess(theapElasticProcess);

   G4AntiProtonInelasticProcess* theAntiProtonInelasticProcess 
                         = new G4AntiProtonInelasticProcess(); 

/*
   G4LEAntiProtonInelastic* theAntiProtonLEPModel = new G4LEAntiProtonInelastic();
   G4HEAntiProtonInelastic* theAntiProtonHEPModel = new G4HEAntiProtonInelastic();
   theAntiProtonInelasticProcess->RegisterMe(theAntiProtonLEPModel);
   theAntiProtonInelasticProcess->RegisterMe(theAntiProtonHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiProtonInelasticProcess);

   G4AntiProtonAbsorptionFritiof* theAntiProtonAnnihilation
                            =  new G4AntiProtonAbsorptionFritiof();
   pManager->AddRestProcess(theAntiProtonAnnihilation);

   G4VProcess* theapMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theapIonisation        = new G4hIonisation();

   pManager->AddProcess(theapIonisation);
   pManager->AddProcess(theapMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theapMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theapIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theapMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theapIonisation,        idxPostStep,2);


// new neutron physics list

  // Neutron
  pManager = G4Neutron::Neutron()->GetProcessManager();
  // add process
  // elastic scattering
  G4HadronElasticProcess* theNeutronElasticProcess =   new G4HadronElasticProcess();
  G4HadronElastic* theElasticModel1 = new G4HadronElastic;
  G4NeutronHPElastic * theElasticNeutron = new G4NeutronHPElastic;
  theNeutronElasticProcess->RegisterMe(theElasticModel1);
  theElasticModel1->SetMinEnergy(0.01*CLHEP::eV);
  theNeutronElasticProcess->RegisterMe(theElasticNeutron);
  theElasticNeutron->SetMaxEnergy(2.*CLHEP::MeV);
  
  G4NeutronHPElasticData * theNeutronData = new G4NeutronHPElasticData;
  theNeutronElasticProcess->AddDataSet(theNeutronData);
  pManager->AddDiscreteProcess(theNeutronElasticProcess);
  // inelastic 
  G4NeutronHPInelastic * theHPNeutronInelasticModel =
    new G4NeutronHPInelastic;
  theHPNeutronInelasticModel->SetMaxEnergy(2.*CLHEP::MeV);
  
  G4NeutronInelasticProcess *theNeutronInelastic=new G4NeutronInelasticProcess();
  
  theNeutronInelastic->RegisterMe(theHPNeutronInelasticModel);
  G4NeutronHPInelasticData * theNeutronData1 = new G4NeutronHPInelasticData;
  theNeutronInelastic->AddDataSet(theNeutronData1);

  // binary
//  G4BinaryCascade * neutronBC = new G4BinaryCascade;
//  neutronBC->SetMinEnergy(19.*MeV);
//  neutronBC->SetMaxEnergy(10.5*GeV);
//  theNeutronInelastic.RegisterMe(neutronBC);
  // higher energy
//  theNeutronInelastic.RegisterMe(theTheoModel);  

  // now the cross-sections.
  G4NeutronInelasticCrossSection * theNeutronData2 = new G4NeutronInelasticCrossSection;
  theNeutronInelastic->AddDataSet(theNeutronData2);
  pManager->AddDiscreteProcess(theNeutronInelastic);
  // fission
  G4HadronFissionProcess *theFissionProcess = new G4HadronFissionProcess;
  G4LFission* theFissionModel = new G4LFission;
  theFissionProcess->RegisterMe(theFissionModel);
  pManager->AddDiscreteProcess(theFissionProcess);

  //capture  
  G4HadronCaptureProcess* theCaptureProcess =
    new G4HadronCaptureProcess();
  G4NeutronRadCapture* theCaptureModel = new G4NeutronRadCapture();
  theCaptureProcess->RegisterMe(theCaptureModel);
  theCaptureModel->SetMinEnergy(0.01*CLHEP::eV);
  G4NeutronHPCapture * theHPNeutronCaptureModel = new G4NeutronHPCapture();
  theCaptureProcess->RegisterMe(theHPNeutronCaptureModel);
  G4NeutronHPCaptureData * theNeutronData3 = new G4NeutronHPCaptureData();
  theCaptureProcess->AddDataSet(theNeutronData3);
  pManager->AddDiscreteProcess(theCaptureProcess);

G4cout << "I registered neutron processes" << G4endl;

///////////////////////////////////////////////////////////////////////

/*
   // neutron Physics
   pManager = G4Neutron::Neutron()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thenElasticProcess 
                         = new G4HadronElasticProcess();
   G4LElastic* thenElasticModel = new G4LElastic();
   thenElasticProcess->RegisterMe(thenElasticModel);
   pManager->AddDiscreteProcess(thenElasticProcess);

   G4NeutronInelasticProcess* theNeutronInelasticProcess 
                         = new G4NeutronInelasticProcess(); 

   G4LENeutronInelastic* theNeutronLEPModel = new G4LENeutronInelastic();
   G4HENeutronInelastic* theNeutronHEPModel = new G4HENeutronInelastic();
   theNeutronInelasticProcess->RegisterMe(theNeutronLEPModel);
   theNeutronInelasticProcess->RegisterMe(theNeutronHEPModel);
   pManager->AddDiscreteProcess(theNeutronInelasticProcess);

   G4HadronFissionProcess* thenFission
                         = new G4HadronFissionProcess();
   G4LFission* thenFissionModel = new G4LFission();
   thenFission->RegisterMe(thenFissionModel);
   pManager->AddDiscreteProcess(thenFission);


   G4HadronCaptureProcess* thenCapture
                         = new G4HadronCaptureProcess();
   G4LCapture* thenCaptureModel = new G4LCapture();
   thenCapture->RegisterMe(thenCaptureModel);
   pManager->AddDiscreteProcess(thenCapture);

*/
   // anti-neutron Physics
   pManager = G4AntiNeutron::AntiNeutron()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theanElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theanElasticModel = new G4HadronElastic();
   theanElasticProcess->RegisterMe(theanElasticModel);
   pManager->AddDiscreteProcess(theanElasticProcess);

   G4AntiNeutronInelasticProcess* theAntiNeutronInelasticProcess 
                         = new G4AntiNeutronInelasticProcess(); 
/*
   G4LEAntiNeutronInelastic* theAntiNeutronLEPModel = new G4LEAntiNeutronInelastic();
   G4HEAntiNeutronInelastic* theAntiNeutronHEPModel = new G4HEAntiNeutronInelastic();
   theAntiNeutronInelasticProcess->RegisterMe(theAntiNeutronLEPModel);
   theAntiNeutronInelasticProcess->RegisterMe(theAntiNeutronHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiNeutronInelasticProcess);

   G4AntiNeutronAnnihilationAtRest* theAntiNeutronAnnihilation
                            =  new G4AntiNeutronAnnihilationAtRest();
   pManager->AddRestProcess(theAntiNeutronAnnihilation);


   // Lambda Physics
   pManager = G4Lambda::Lambda()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thel0ElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thel0ElasticModel = new G4HadronElastic();
   thel0ElasticProcess->RegisterMe(thel0ElasticModel);
   pManager->AddDiscreteProcess(thel0ElasticProcess);

   G4LambdaInelasticProcess* theLambdaInelasticProcess 
                         = new G4LambdaInelasticProcess(); 
/*
   G4LELambdaInelastic* theLambdaLEPModel = new G4LELambdaInelastic();
   G4HELambdaInelastic* theLambdaHEPModel = new G4HELambdaInelastic();
   theLambdaInelasticProcess->RegisterMe(theLambdaLEPModel);
   theLambdaInelasticProcess->RegisterMe(theLambdaHEPModel);
*/  
   pManager->AddDiscreteProcess(theLambdaInelasticProcess);


   // Anti-Labda Physics
   pManager = G4AntiLambda::AntiLambda()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theal0ElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theal0ElasticModel = new G4HadronElastic();
   theal0ElasticProcess->RegisterMe(theal0ElasticModel);
   pManager->AddDiscreteProcess(theal0ElasticProcess);

   G4AntiLambdaInelasticProcess* theAntiLambdaInelasticProcess 
                         = new G4AntiLambdaInelasticProcess(); 

/*
   G4LEAntiLambdaInelastic* theAntiLambdaLEPModel = new G4LEAntiLambdaInelastic();
   G4HEAntiLambdaInelastic* theAntiLambdaHEPModel = new G4HEAntiLambdaInelastic();
   theAntiLambdaInelasticProcess->RegisterMe(theAntiLambdaLEPModel);
   theAntiLambdaInelasticProcess->RegisterMe(theAntiLambdaHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiLambdaInelasticProcess);


   // Sigma+ Physics
   pManager = G4SigmaPlus::SigmaPlus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thespElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thespElasticModel = new G4HadronElastic();
   thespElasticProcess->RegisterMe(thespElasticModel);
   pManager->AddDiscreteProcess(thespElasticProcess);

   G4SigmaPlusInelasticProcess* theSigmaPlusInelasticProcess 
                         = new G4SigmaPlusInelasticProcess(); 

/*
   G4LESigmaPlusInelastic* theSigmaPlusLEPModel = new G4LESigmaPlusInelastic();
   G4HESigmaPlusInelastic* theSigmaPlusHEPModel = new G4HESigmaPlusInelastic();
   theSigmaPlusInelasticProcess->RegisterMe(theSigmaPlusLEPModel);
   theSigmaPlusInelasticProcess->RegisterMe(theSigmaPlusHEPModel);
*/  
   pManager->AddDiscreteProcess(theSigmaPlusInelasticProcess);

   G4VProcess* thespMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thespIonisation        = new G4hIonisation();

   pManager->AddProcess(thespIonisation);
   pManager->AddProcess(thespMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thespMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thespIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thespMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thespIonisation,        idxPostStep,2);


   // anti-Sigma+ Physics
   pManager = G4AntiSigmaPlus::AntiSigmaPlus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaspElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theaspElasticModel = new G4HadronElastic();
   theaspElasticProcess->RegisterMe(theaspElasticModel);
   pManager->AddDiscreteProcess(theaspElasticProcess);

   G4AntiSigmaPlusInelasticProcess* theAntiSigmaPlusInelasticProcess 
                         = new G4AntiSigmaPlusInelasticProcess(); 

/*
   G4LEAntiSigmaPlusInelastic* theAntiSigmaPlusLEPModel = new G4LEAntiSigmaPlusInelastic();
   G4HEAntiSigmaPlusInelastic* theAntiSigmaPlusHEPModel = new G4HEAntiSigmaPlusInelastic();
   theAntiSigmaPlusInelasticProcess->RegisterMe(theAntiSigmaPlusLEPModel);
   theAntiSigmaPlusInelasticProcess->RegisterMe(theAntiSigmaPlusHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiSigmaPlusInelasticProcess);

   G4VProcess* theaspMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaspIonisation        = new G4hIonisation();

   pManager->AddProcess(theaspIonisation);
   pManager->AddProcess(theaspMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaspMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaspIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaspMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaspIonisation,        idxPostStep,2);


   // Sigma- Physics
   pManager = G4SigmaMinus::SigmaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thesmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thesmElasticModel = new G4HadronElastic();
   thesmElasticProcess->RegisterMe(thesmElasticModel);
   pManager->AddDiscreteProcess(thesmElasticProcess);

   G4SigmaMinusInelasticProcess* theSigmaMinusInelasticProcess 
                         = new G4SigmaMinusInelasticProcess(); 

/*
   G4LESigmaMinusInelastic* theSigmaMinusLEPModel = new G4LESigmaMinusInelastic();
   G4HESigmaMinusInelastic* theSigmaMinusHEPModel = new G4HESigmaMinusInelastic();
   theSigmaMinusInelasticProcess->RegisterMe(theSigmaMinusLEPModel);
   theSigmaMinusInelasticProcess->RegisterMe(theSigmaMinusHEPModel);
*/   
  pManager->AddDiscreteProcess(theSigmaMinusInelasticProcess);

   G4VProcess* thesmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thesmIonisation        = new G4hIonisation();

   pManager->AddProcess(thesmIonisation);
   pManager->AddProcess(thesmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thesmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thesmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thesmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thesmIonisation,        idxPostStep,2);


   // anti-Sigma- Physics
   pManager = G4AntiSigmaMinus::AntiSigmaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theasmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theasmElasticModel = new G4HadronElastic();
   theasmElasticProcess->RegisterMe(theasmElasticModel);
   pManager->AddDiscreteProcess(theasmElasticProcess);

   G4AntiSigmaMinusInelasticProcess* theAntiSigmaMinusInelasticProcess 
                         = new G4AntiSigmaMinusInelasticProcess(); 

/*
   G4LEAntiSigmaMinusInelastic* theAntiSigmaMinusLEPModel = new G4LEAntiSigmaMinusInelastic();
   G4HEAntiSigmaMinusInelastic* theAntiSigmaMinusHEPModel = new G4HEAntiSigmaMinusInelastic();
   theAntiSigmaMinusInelasticProcess->RegisterMe(theAntiSigmaMinusLEPModel);
   theAntiSigmaMinusInelasticProcess->RegisterMe(theAntiSigmaMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiSigmaMinusInelasticProcess);

   G4VProcess* theasmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theasmIonisation        = new G4hIonisation();

   pManager->AddProcess(theasmIonisation);
   pManager->AddProcess(theasmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theasmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theasmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theasmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theasmIonisation,        idxPostStep,2);


   // Xi0 Physics
   pManager = G4XiZero::XiZero()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thex0ElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thex0ElasticModel = new G4HadronElastic();
   thex0ElasticProcess->RegisterMe(thex0ElasticModel);
   pManager->AddDiscreteProcess(thex0ElasticProcess);

   G4XiZeroInelasticProcess* theXiZeroInelasticProcess 
                         = new G4XiZeroInelasticProcess(); 

/*
   G4LEXiZeroInelastic* theXiZeroLEPModel = new G4LEXiZeroInelastic();
   G4HEXiZeroInelastic* theXiZeroHEPModel = new G4HEXiZeroInelastic();
   theXiZeroInelasticProcess->RegisterMe(theXiZeroLEPModel);
   theXiZeroInelasticProcess->RegisterMe(theXiZeroHEPModel);
*/  
   pManager->AddDiscreteProcess(theXiZeroInelasticProcess);


   // Anti-Xi0 Physics
   pManager = G4AntiXiZero::AntiXiZero()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theax0ElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theax0ElasticModel = new G4HadronElastic();
   theax0ElasticProcess->RegisterMe(theax0ElasticModel);
   pManager->AddDiscreteProcess(theax0ElasticProcess);

   G4AntiXiZeroInelasticProcess* theAntiXiZeroInelasticProcess 
                         = new G4AntiXiZeroInelasticProcess(); 

/*
   G4LEAntiXiZeroInelastic* theAntiXiZeroLEPModel = new G4LEAntiXiZeroInelastic();
   G4HEAntiXiZeroInelastic* theAntiXiZeroHEPModel = new G4HEAntiXiZeroInelastic();
   theAntiXiZeroInelasticProcess->RegisterMe(theAntiXiZeroLEPModel);
   theAntiXiZeroInelasticProcess->RegisterMe(theAntiXiZeroHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiXiZeroInelasticProcess);


   // Xi- Physics
   pManager = G4XiMinus::XiMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* thexmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* thexmElasticModel = new G4HadronElastic();
   thexmElasticProcess->RegisterMe(thexmElasticModel);
   pManager->AddDiscreteProcess(thexmElasticProcess);

   G4XiMinusInelasticProcess* theXiMinusInelasticProcess 
                         = new G4XiMinusInelasticProcess(); 

/*
   G4LEXiMinusInelastic* theXiMinusLEPModel = new G4LEXiMinusInelastic();
   G4HEXiMinusInelastic* theXiMinusHEPModel = new G4HEXiMinusInelastic();
   theXiMinusInelasticProcess->RegisterMe(theXiMinusLEPModel);
   theXiMinusInelasticProcess->RegisterMe(theXiMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theXiMinusInelasticProcess);

   G4VProcess* thexmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* thexmIonisation        = new G4hIonisation();

   pManager->AddProcess(thexmIonisation);
   pManager->AddProcess(thexmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(thexmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(thexmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(thexmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(thexmIonisation,        idxPostStep,2);


   // anti-Xi- Physics
   pManager = G4AntiXiMinus::AntiXiMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaxmElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theaxmElasticModel = new G4HadronElastic();
   theaxmElasticProcess->RegisterMe(theaxmElasticModel);
   pManager->AddDiscreteProcess(theaxmElasticProcess);

   G4AntiXiMinusInelasticProcess* theAntiXiMinusInelasticProcess 
                         = new G4AntiXiMinusInelasticProcess(); 

/*
   G4LEAntiXiMinusInelastic* theAntiXiMinusLEPModel = new G4LEAntiXiMinusInelastic();
   G4HEAntiXiMinusInelastic* theAntiXiMinusHEPModel = new G4HEAntiXiMinusInelastic();
   theAntiXiMinusInelasticProcess->RegisterMe(theAntiXiMinusLEPModel);
   theAntiXiMinusInelasticProcess->RegisterMe(theAntiXiMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiXiMinusInelasticProcess);

   G4VProcess* theaxmMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaxmIonisation        = new G4hIonisation();

   pManager->AddProcess(theaxmIonisation);
   pManager->AddProcess(theaxmMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaxmMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaxmIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaxmMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaxmIonisation,        idxPostStep,2);


   // Omega- Physics
   pManager = G4OmegaMinus::OmegaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theomElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theomElasticModel = new G4HadronElastic();
   theomElasticProcess->RegisterMe(theomElasticModel);
   pManager->AddDiscreteProcess(theomElasticProcess);

   G4OmegaMinusInelasticProcess* theOmegaMinusInelasticProcess 
                         = new G4OmegaMinusInelasticProcess(); 

/*
   G4LEOmegaMinusInelastic* theOmegaMinusLEPModel = new G4LEOmegaMinusInelastic();
   G4HEOmegaMinusInelastic* theOmegaMinusHEPModel = new G4HEOmegaMinusInelastic();
   theOmegaMinusInelasticProcess->RegisterMe(theOmegaMinusLEPModel);
   theOmegaMinusInelasticProcess->RegisterMe(theOmegaMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theOmegaMinusInelasticProcess);

   G4VProcess* theomMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theomIonisation        = new G4hIonisation();

   pManager->AddProcess(theomIonisation);
   pManager->AddProcess(theomMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theomMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theomIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theomMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theomIonisation,        idxPostStep,2);


   // anti-Omega- Physics
   pManager = G4AntiOmegaMinus::AntiOmegaMinus()->GetProcessManager();

   // add process
   G4HadronElasticProcess* theaomElasticProcess 
                         = new G4HadronElasticProcess();
   G4HadronElastic* theaomElasticModel = new G4HadronElastic();
   theaomElasticProcess->RegisterMe(theaomElasticModel);
   pManager->AddDiscreteProcess(theaomElasticProcess);

   G4AntiOmegaMinusInelasticProcess* theAntiOmegaMinusInelasticProcess 
                         = new G4AntiOmegaMinusInelasticProcess(); 

/*
   G4LEAntiOmegaMinusInelastic* theAntiOmegaMinusLEPModel = new G4LEAntiOmegaMinusInelastic();
   G4HEAntiOmegaMinusInelastic* theAntiOmegaMinusHEPModel = new G4HEAntiOmegaMinusInelastic();
   theAntiOmegaMinusInelasticProcess->RegisterMe(theAntiOmegaMinusLEPModel);
   theAntiOmegaMinusInelasticProcess->RegisterMe(theAntiOmegaMinusHEPModel);
*/  
   pManager->AddDiscreteProcess(theAntiOmegaMinusInelasticProcess);

   G4VProcess* theaomMultipleScattering = new G4hMultipleScattering();
   G4VProcess* theaomIonisation        = new G4hIonisation();

   pManager->AddProcess(theaomIonisation);
   pManager->AddProcess(theaomMultipleScattering);

   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theaomMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theaomIonisation,        idxAlongStep,2);
   // 
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theaomMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theaomIonisation,        idxPostStep,2);


}
