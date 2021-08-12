#include "FemMembranes.hpp"
namespace mdx
{

  bool FemMembranes::initialize(QWidget *parent)
  {
    mesh = currentMesh();
    if(!mesh)
      throw(QString("FemMembranes::initialize No current mesh"));

    ccName = mesh->ccName();
    if(ccName.isEmpty())
      throw(QString("FemMembranes::initialize No cell complex"));

    cs = &mesh->ccStructure(ccName);

    // Get the solver process
    if(!getProcess(parm("Solver Process"), solverProcess))
      throw(QString("FemMembranes::initialize Unable to make solver process: %1").arg(parm("Solver Process")));
    solverProcess->initialize(parent);

    return true;
  }

  bool FemMembranes::step()
  {
    if(!solverProcess)
      throw(QString("FemMembranes::run Solver process pointer invalid"));
        // Reinitialize solver with new graph
    solverProcess->initSolver(cs);
    solverProcess->step();
    mesh->updatePositions(ccName);

    return true;
  }

  bool FemMembranes::rewind(QWidget *parent)
  {
    // To rewind, we'll reload the mesh
    Mesh *mesh = currentMesh();
    if(!mesh or mesh->file().isEmpty())
      throw(QString("No current mesh, cannot rewind"));
    MeshLoad meshLoad(*this);
    meshLoad.setParm("File Name", mesh->file());
    return meshLoad.run();
  }

  bool FemMembranes::finalize(QWidget *parent)
  {
    if(!solverProcess)
      throw(QString("FemMembranes::run Solver process pointer invalid"));

    bool result = solverProcess->finalize(parent);

    // Cleanup
    mesh = 0;
    solverProcess = 0;

    return result;
  }

  
    
  
  REGISTER_PROCESS(FemMembranes);
  REGISTER_PROCESS(FemMembraneSolver);
  REGISTER_PROCESS(FemMembraneRefCfg);
  REGISTER_PROCESS(FemMembraneStressStrain);
  REGISTER_PROCESS(FemMembraneDerivs);
  REGISTER_PROCESS(FemMembraneMaterial);
  REGISTER_PROCESS(FemMembraneCellFacesMaterial);
  REGISTER_PROCESS(FemMembraneAnisoDir);
  REGISTER_PROCESS(FemMembranePressure);
  REGISTER_PROCESS(FemMembranePressureDerivs);
 
  REGISTER_PROCESS(FemMembraneSetDirichlet);
  REGISTER_PROCESS(FemMembraneDirichletDerivs);



  REGISTER_PROCESS(FemMembraneVisMaterial);
  REGISTER_PROCESS(FemMembraneComputeCurrentDirections);
  REGISTER_PROCESS(FemMembraneVisDirections);
  REGISTER_PROCESS(FemAnisotropyPropagationFailure);

}
