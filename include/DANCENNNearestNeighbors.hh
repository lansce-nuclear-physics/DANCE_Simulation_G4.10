
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



//--------------------------------------------------------------------------------
/*!\class	NNNearestNeighbors
 * \brief	This class lists handles the nearest neighbors mapping.
 * \methods
 *			\li \b 	NNNearestNeighbors		- Constructor
 *			\li \b 	~NNNearestNeighbors		- Destructor
 *			\li \b	NNInitialize			- Create in memory map of nearest neighbors
 *											  for each crystal.
 *			\li \b  NNIsNeighbor			- Determine if crystal is neighbor of
 *											  another crystal.
 * \note	
 * \author	Jan M. Wouters
 * \history	2003-06-10 (jmw) - Original.
 */
//--------------------------------------------------------------------------------
#ifndef DANCENNNearestNeighbors_h
#define DANCENNNearestNeighbors_h 1

#include <map>
#include <string>

const short NNcNoNeighbor = 200;
const short NNcMaxCrystals = 165;
const short NNcIsNeighbor = 1;
const short NNcError = -1;
const short NNcMaxNearestNeighbors = 7;

//--------------------------------------------------------------------------------
// Class NNNearestNeighbors
//--------------------------------------------------------------------------------
class NNNearestNeighbors
{
	public:
		static NNNearestNeighbors *Instance();
		
		
		bool			NNInitialize( const std::string &asFilename );	
		short			NNIsNeighbor( short aRefCrystal, short aTestCrystal );
        void			NNPrintMap( void );
		
// Class variables
	private:
		short				NNgNeighborMap[ NNcMaxCrystals ][ NNcMaxNearestNeighbors ]; 

		NNNearestNeighbors();
		~NNNearestNeighbors();
};

#endif

