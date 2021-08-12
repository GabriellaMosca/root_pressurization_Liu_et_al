# root_pressurization_Liu_et_al 
 
[![DOI](https://zenodo.org/badge/395295069.svg)](https://zenodo.org/badge/latestdoi/395295069)
Pressurization Model for Liu et al.

The following installation was tested on Ubuntu 20.04

Requirements:
- MorphoDynamX (MDX - www.MorphoDynamX.org) --> installation package from the 'MDX' subfolder in this repository: https://gitlab.mpcdf.mpg.de/sstrauss/root-pressurization-model-for-liu-et-al/-/tree/master/MDX

- MorphoDynamX installation instructions can be found here: https://raw.githubusercontent.com/GabriellaMosca/MorphoMechanX/main/InstallationInstructions.pdf

How to start:

- Open the model folder (EmbrioAnisotropic) in a console
- type: make clean
- type: make
- type: make run
- MDX opens up with the model processes and predefined mesh (which the user can change)
- In the right panel, under Model/Process/CCF  double click on "01 FEM Membranes"

How to set up your own model:

-- Load a mesh. There are several meshes that were used in the paper in the 'meshes' subfolder
-- Assign the reference configuration (double click on 04 Reference Configuration)
-- Set Material Properties (double click on 06 Material Properties with the parameters set to wished values)
-- Only for anisotropic material: Run (double click) "08a Set Aniso Dir" with default parameters
-- Run "09a Set Pressure" (select all the faces before )
-- The mesh should be saved before continuing
-- Pressurize the template by running (double clicking on) "01 FEM Membranes"
-- wait until convergence is reached and the process terminates


More templates and parameters for different models are available under the open access repository: https://gitlab.mpcdf.mpg.de/sstrauss/root-pressurization-model-for-liu-et-al/
For questions about the model contact gabriella.mosca@gmail.com, strauss@mpipz.mpg.de
