
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
// $Id: DANCEGeneralPhysics.hh,v 1.4 2004/11/23 04:02:02 tkoi Exp $
// --------------------------------------------------------------
//

#ifndef DANCEGeneralPhysics_h
#define DANCEGeneralPhysics_h 1

#include "globals.hh"
#include "G4ios.hh"

#include "G4VPhysicsConstructor.hh"

class DANCEGeneralPhysics : public G4VPhysicsConstructor
{
  public:
    DANCEGeneralPhysics(const G4String& name = "general");
    virtual ~DANCEGeneralPhysics();

  public:
    // This method will be invoked in the Construct() method.
    // each particle type will be instantiated
    virtual void ConstructParticle();

    // This method will be invoked in the Construct() method.
    // each physics process will be instantiated and
    // registered to the process manager of each particle type
    virtual void ConstructProcess();

};


#endif







