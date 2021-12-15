#ifdef ANCIL
#include "AgataAncillaryLNLChamb.hh"
#include "AgataDetectorAncillary.hh"
#include "AgataDetectorConstruction.hh"
#include "AgataSensitiveDetector.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Sphere.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4PVPlacement.hh"
#include "G4SubtractionSolid.hh"
#include "G4UnionSolid.hh"

#include "G4SDManager.hh"

#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RunManager.hh"
#include "G4ios.hh"


AgataAncillaryLNLChamb::AgataAncillaryLNLChamb(G4String path, G4String name )
{
  // dummy assignment needed for compatibility with other implementations of this class
  G4String iniPath     = path;
  
  dirName     = name;

  
  matShell    = NULL;
  matName     = "Aluminum";


  ancSD       = NULL;
  ancName     = G4String("LNLChamb");
  ancOffset   = 35000;
  
  numAncSd = 0;
}



AgataAncillaryLNLChamb::~AgataAncillaryLNLChamb()
{}
#include "G4NistManager.hh"


G4int AgataAncillaryLNLChamb::FindMaterials()
{
  // search the material by its name
  G4Material* ptMaterial =
    G4NistManager::Instance()->FindOrBuildMaterial("G4_Al");//G4Material::GetMaterial(matName);
  if (ptMaterial) {
    matShell = ptMaterial;
    G4String nome = matShell->GetName();
    G4cout << "\n----> The ancillary material is "
          << nome << G4endl;
  }
  else {
    G4cout << " Could not find the material " << matName << G4endl;
    G4cout << " Could not build the ancillary brick! " << G4endl;
    return 1;
  }  
  return 0;
}

void AgataAncillaryLNLChamb::InitSensitiveDetector()
{}


void AgataAncillaryLNLChamb::GetDetectorConstruction()
{  
	
  G4RunManager* runManager = G4RunManager::GetRunManager();
  theDetector  = (AgataDetectorConstruction*)(runManager->GetUserDetectorConstruction());
  
}


void AgataAncillaryLNLChamb::Placement()
{	
 
  m_gdmlparser.Read("/data/SIM_AGATA/trunk/LNL_gdml/assembly_LNL_chamb.gdml");
  m_LogicalVol= m_gdmlparser.GetVolume("ReactChamber");


    G4RotationMatrix* rm= new G4RotationMatrix();
    G4RotationMatrix rmY, rmZ;
	rmZ.rotateZ(0.*deg);
	rmY.rotateY(0.*deg);
   
	*rm=rmY*rmZ;

	//G4Transform3D TF(rm, rm*G4ThreeVector(0., 0., 0.));

    // gdml World box
    //m_LogicalVol->SetVisAttributes(G4VisAttributes::Invisible); 
    G4VisAttributes *AttVol = new G4VisAttributes(G4Colour(1.0, 1.0, 0.0)); 
    AttVol->SetForceSolid(true);
   
    
     
    new G4PVPlacement(rm, G4ThreeVector(0., 0., 0.), "ReactChamber", m_LogicalVol, theDetector->HallPhys(), false, 0 );

	return ;
  
}


void AgataAncillaryLNLChamb::ShowStatus()
{
  G4cout << " LNL Chamber support has been constructed." << G4endl;
}

void AgataAncillaryLNLChamb::WriteHeader(std::ofstream &/*outFileLMD*/, G4double /*unit*/)
{}

#endif
