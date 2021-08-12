#ifndef FEM_MEMBRANES_HPP
#define FEM_MEMBRANES_HPP

#include <MDXProcessFem.hpp>
#include <MDXProcessFemMorphogen.hpp>
#include <MeshProcessSystem.hpp>
#include <MeshProcessStructure.hpp>
#include <MDXProcessTissue.hpp>
#include <MDXProcessCellDivide.hpp>
#include <Attributes.hpp>
#include <MeshProcessSystemRender.hpp>
#include <MeshUtils.hpp>
#include <MeshProcessSelection.hpp>
#include <MeshProcessMeasures3D.hpp>
#include <Triangle3.hpp>

#include <Solver.hpp>
namespace mdx
{
  class FemMembranes;
  class FemMembraneSolver;
  class FemMembraneBisect;


  // Main model class
  class FemMembranes : public Process
  {
  public:
    FemMembranes(const Process &proc) : Process(proc) 
    {
      setName("Model/CCF/01 FEM Membranes");
      setDesc("FEM simulation with growth and subdivision");

      addParm("Solver Process", "Name of solver process", "Model/CCF/02 FEM Solver");

    } 
   

    bool initialize(QWidget *parent);
    bool step();
    bool rewind(QWidget *parent);
    bool finalize(QWidget *parent);
    

  private:
    Mesh *mesh = 0;
    QString ccName;
    CCStructure *cs = 0;

    FemMembraneSolver *solverProcess = 0;

  };

  class FemMembraneSolver : public fem::FemSolver
  {
  public:
    FemMembraneSolver(const Process &proc) : fem::FemSolver(proc) 
    {
      setName("Model/CCF/02 FEM Solver");
      setDesc("FEM Simulation using triangular membrane elements");

      // Update parameters with our own defaults
      setParmDefault("Stress-Strain", "Model/CCF/05 Stress-Strain");

      // Add derivatives processes
      addParm("Element Derivs", "Process for element derivatives", "Model/CCF/03 Triangle Derivs");
      addParm("Pressure Derivs", "Process for pressure derivatives", "Model/CCF/10 Pressure Derivs"); 
      addParm("Dirichlet Derivs", "Process for Dirichlet derivatives", "Model/CCF/16 Dirichlet Derivs");
    }
  };

  class FemMembraneDerivs : public fem::ElementDerivs
  {
  public:
    FemMembraneDerivs(const Process &proc) : ElementDerivs(proc) 
    {
      setName("Model/CCF/03 Triangle Derivs");

      setParmDefault("Element Type", "Linear Triangle");
      setParmDefault("Element Attribute", "Triangle Element");
    }
  };

  class FemMembraneRefCfg : public fem::SetRefCfg
  {
  public:
    FemMembraneRefCfg(const Process &proc) : SetRefCfg(proc) 
    {
      setName("Model/CCF/04 Reference Configuration");

      addParm("Thickness", "Thickness of the membrane element", "1.0");
      setParmDefault("Element Type", "Linear Triangle");
      setParmDefault("Element Attribute", "Triangle Element");
    }
  };

  class FemMembraneStressStrain : public fem::StressStrain
  {
  public:
    FemMembraneStressStrain(const Process &proc) : StressStrain(proc) 
    {
      setName("Model/CCF/05 Stress-Strain");

      setParmDefault("Element Type", "Linear Triangle");
      setParmDefault("Element Attribute", "Triangle Element");
    }
  };

  class FemMembraneMaterial : public fem::SetTransIsoMaterial
  {
  public:
    FemMembraneMaterial(const Process &proc) : SetTransIsoMaterial(proc) 
    {
      setName("Model/CCF/06 Material Properties");
    }
  };

  
  class FemMembraneCellFacesMaterial : public fem::CellsToFacesTransIsoMaterial
  {
  public:
    FemMembraneCellFacesMaterial(const Process &proc) : CellsToFacesTransIsoMaterial(proc) 
    {
      setName("Model/CCF/07 Cells to Faces Material");
    }
  };

  class FemMembraneAnisoDir : public fem::SetAnisoDir
  {
  public:
    FemMembraneAnisoDir(const Process &proc) : SetAnisoDir(proc) 
    {
      setName("Model/CCF/08 Set Aniso Dir");

      setParmDefault("Element Type", "Linear Triangle");
      setParmDefault("Element Attribute", "Triangle Element");
    }
  };

 
  class FemMembranePressure : public fem::SetPressure
  {
  public:
    FemMembranePressure(const Process &proc) : SetPressure(proc) 
    {
      setName("Model/CCF/09 Set Pressure");
    }
  };

  class FemMembranePressureDerivs : public fem::PressureDerivs
  {
  public:
    FemMembranePressureDerivs(const Process &proc) : PressureDerivs(proc) 
    {
      setName("Model/CCF/10 Pressure Derivs");
    }
  };

 
  class FemMembraneComputeCurrentDirections : public fem::ComputeCurrentDirections
  {
    public:
      FemMembraneComputeCurrentDirections(const Process &proc) : ComputeCurrentDirections(proc)
      {
        setName("Model/CCF/17 Compute Current Directions") ;
      }
  };

  class FemMembraneVisDirections : public fem::VisDirections
  {
    public:
      FemMembraneVisDirections(const Process &proc) : VisDirections(proc)
      {
        setName("Model/CCF/18 Visualize Directions") ;
      }
  };

  class FemMembraneSetDirichlet : public fem::SetDirichlet
  {
  public:
    FemMembraneSetDirichlet(const Process &proc) : SetDirichlet(proc) 
    {
      setName("Model/CCF/15 Set Dirichlet");
    }
  };

  class FemMembraneDirichletDerivs : public fem::DirichletDerivs
  {
  public:
    FemMembraneDirichletDerivs(const Process &proc) : DirichletDerivs(proc) 
    {
      setName("Model/CCF/16 Dirichlet Derivs");
    }
  };
 
  class FemMembraneVisMaterial : public fem::VisTransIsoMaterial
  {
  public:
    FemMembraneVisMaterial(const Process &proc) : VisTransIsoMaterial(proc) 
    {
      setName("Model/CCF/20 Visualize Material");
    }
  };


  class FemAnisotropyPropagationFailure : public fem::DisplayFailedAnisotropyPropagation
  { 
    public:
    FemAnisotropyPropagationFailure(const Process &proc) : DisplayFailedAnisotropyPropagation(proc) 
    {
      setName("Model/CCF/22 Display Anisotropy Propagation Failure");
    }
  };
 
}
#endif

