
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


//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
// $Id: DANCEEMPhysics.cc,v 1.7 2004/11/23 04:02:02 tkoi Exp $
// --------------------------------------------------------------
//
//
// 09-Oct-2003 Change gamma, electron, positorn process T. Koi
// 10-Jan-2004 Add Brems. of AlongStepDoIt for e+- T. Koi


#include "DANCEEMPhysics.hh"

#include "globals.hh"
#include "G4ios.hh"
#include <iomanip>


DANCEEMPhysics::DANCEEMPhysics(const G4String& name)
               :  G4VPhysicsConstructor(name)
{
}

DANCEEMPhysics::~DANCEEMPhysics()
{
}

#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"

#include "G4Gamma.hh"
#include "G4GenericIon.hh"

#include "G4Electron.hh"
#include "G4Positron.hh"

#include "G4NeutrinoE.hh"
#include "G4AntiNeutrinoE.hh"

#include "G4ProcessManager.hh"

//#include "G4hLowEnergyIonisation.hh"
#include "G4hIonisation.hh"
#include "G4ionIonisation.hh"

// gamma
//#include "G4LowEnergyRayleigh.hh" 
#include "G4RayleighScattering.hh"
//#include "G4LowEnergyPhotoElectric.hh"
#include "G4PhotoElectricEffect.hh"
//#include "G4LowEnergyCompton.hh"  
#include "G4ComptonScattering.hh"
//#include "G4LowEnergyGammaConversion.hh" 
#include "G4GammaConversion.hh"
// e-
//#include "G4LowEnergyIonisation.hh" 
//#include "G4LowEnergyBremsstrahlung.hh" 
// e+
#include "G4eIonisation.hh" 
#include "G4eBremsstrahlung.hh" 
#include "G4eplusAnnihilation.hh"


// Penelope physics lists
//#include "G4PenelopeCompton.hh"
//#include "G4PenelopeGammaConversion.hh"
//#include "G4PenelopePhotoElectric.hh"
//#include "G4PenelopeIonisation.hh"
//#include "G4PenelopeBremsstrahlung.hh"
//#include "G4PenelopeAnnihilation.hh"

#include "G4PenelopeComptonModel.hh"
#include "G4PenelopeGammaConversionModel.hh"
#include "G4PenelopePhotoElectricModel.hh"
#include "G4PenelopeIonisationModel.hh"
#include "G4PenelopeBremsstrahlungModel.hh"
#include "G4PenelopeAnnihilationModel.hh"

void DANCEEMPhysics::ConstructProcess()
{
   G4ProcessManager * pManager = 0;

   //Gamma
   pManager = G4Gamma::Gamma()->GetProcessManager();

//	Standard EM
   	pManager->AddDiscreteProcess(new G4GammaConversion());   // pair production
   	pManager->AddDiscreteProcess(new G4ComptonScattering());
   	pManager->AddDiscreteProcess(new G4PhotoElectricEffect());
	pManager->AddDiscreteProcess(new G4RayleighScattering());


// 	Low Energy
//      pManager->AddDiscreteProcess(new G4LowEnergyRayleigh);
//      pManager->AddDiscreteProcess(new G4LowEnergyPhotoElectric);      
//      pManager->AddDiscreteProcess(new G4LowEnergyCompton);
//      pManager->AddDiscreteProcess(new G4LowEnergyGammaConversion);

//	Penelope Lists

//      pManager->AddDiscreteProcess(new G4PenelopePhotoElectric);
//      pManager->AddDiscreteProcess(new G4PenelopeCompton);
//      pManager->AddDiscreteProcess(new G4PenelopeGammaConversion);


   //Electron
	   pManager = G4Electron::Electron()->GetProcessManager();


	   G4VProcess* theeminusMultipleScattering = new G4eMultipleScattering();
   		pManager->AddProcess(theeminusMultipleScattering, -1,1,1);
//	   	pManager->SetProcessOrdering(theeminusMultipleScattering, idxAlongStep,1);
//   		pManager->SetProcessOrdering(theeminusMultipleScattering, idxPostStep,1);

// Standard EM

//   	G4VProcess* theeminusIonisation         = new G4eIonisation();
//   	G4VProcess* theeminusBremsstrahlung     = new G4eBremsstrahlung();
    
   //  add process
//   	pManager->AddProcess(theeminusIonisation);
//   	pManager->AddProcess(theeminusBremsstrahlung);
   
   // set ordering for AlongStepDoIt
//   	pManager->SetProcessOrdering(theeminusIonisation,         idxAlongStep,2);
//   	pManager->SetProcessOrdering(theeminusBremsstrahlung,     idxAlongStep,3);
   
   // set ordering for PostStepDoIt
//   	pManager->SetProcessOrdering(theeminusIonisation,         idxPostStep,2);
//   	pManager->SetProcessOrdering(theeminusBremsstrahlung,     idxPostStep,3);

// low energy stuff
// commenting out references to LowEnergy physics models, trying to rewrite for Penelope models
//    G4LowEnergyIonisation*  loweIon  = new G4LowEnergyIonisation("LowEnergyIoni");
//    G4eIonisation*  eIon  = new G4eIonisation("Ioni");
//    G4eBremsstrahlung*  eBrem = new G4eBremsstrahlung("eBrem");
//      eBrem->SetAngularGenerator("tsai");
//      pManager->AddProcess(eIon,     -1, 2,2);
//      pManager->AddProcess(eBrem,    -1,-1,3);

//    G4LowEnergyBremsstrahlung*  loweBrem = new G4LowEnergyBremsstrahlung("LowEnBrem");
//      loweBrem->SetAngularGenerator("tsai");
//      pManager->AddProcess(loweIon,     -1, 2,2);
//      pManager->AddProcess(loweBrem,    -1,-1,3);      

// Standard EM Models (these work)
    G4eBremsstrahlung* eBrem = new G4eBremsstrahlung("eBrem");
	pManager->AddProcess(eBrem,    -1,-1,3);
    G4eIonisation* eIon = new G4eIonisation("Ioni");
	pManager->AddProcess(eIon,     -1,2,2);



// Penelope Ionisation and Bremsstrahlung 
//    G4PenelopeBremsstrahlungModel*  PBrem = new G4PenelopeBremsstrahlungModel(0,"PenBrem");
//      pManager->AddProcess(eIon,        -1, 2,2);
//      pManager->AddProcess(PBrem,    -1,-1,3);

// Trying to get Penelope to work
//    G4VProcess* PenBremsstrahlung = new G4PenelopeBremsstrahlungModel();
//    pManager->AddProcess(PenBremsstrahlung);




   //Positron

   pManager = G4Positron::Positron()->GetProcessManager();


   G4VProcess* theeplusMultipleScattering = new G4eMultipleScattering();
   G4VProcess* theeplusIonisation         = new G4eIonisation();
   G4VProcess* theeplusBremsstrahlung     = new G4eBremsstrahlung();
   G4VProcess* theeplusAnnihilation       = new G4eplusAnnihilation();
   G4VProcess* theeplusStepLimiter       = new G4StepLimiter();

   pManager->AddProcess(theeplusMultipleScattering);
   pManager->AddProcess(theeplusIonisation);
   pManager->AddProcess(theeplusBremsstrahlung);
   pManager->AddProcess(theeplusAnnihilation);
   pManager->AddProcess(theeplusStepLimiter,      -1,-1,3);
   //
   // set ordering for AtRestDoIt
   pManager->SetProcessOrderingToFirst(theeplusAnnihilation, idxAtRest);
   //
   // set ordering for AlongStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxAlongStep,1);
   pManager->SetProcessOrdering(theeplusIonisation,         idxAlongStep,2);
   pManager->SetProcessOrdering(theeplusBremsstrahlung,     idxAlongStep,3);
   //
   // set ordering for PostStepDoIt
   pManager->SetProcessOrdering(theeplusMultipleScattering, idxPostStep,1);
   pManager->SetProcessOrdering(theeplusIonisation,         idxPostStep,2);
   pManager->SetProcessOrdering(theeplusBremsstrahlung,     idxPostStep,3);
   pManager->SetProcessOrdering(theeplusAnnihilation,       idxPostStep,4);



// Penelope
//I'll try replacing AddProcess with AddDiscreteProcess. Update: don't do that.

//      pManager->AddProcess(new G4eMultipleScattering,        -1, 1,1);
//      pManager->AddProcess(new G4PenelopeIonisationModel,        -1, 2,2);
//      pManager->AddProcess(new G4PenelopeBremsstrahlungModel,    -1,-1,3);
//      pManager->AddProcess(new G4PenelopeAnnihilationModel,       0,-1,4);

}
