#!/bin/bash
#SBATCH --account=def-oforion        # Replace with your account name if different
#SBATCH --ntasks=10                  # Total number of tasks (10 tasks total)
#SBATCH --mem-per-cpu=10G           # 10 GB of memory per task
#SBATCH --time=7-00:00               # Time limit (days-hours:minutes)
#SBATCH --job-name=karma_sim         # Job name
#SBATCH --output=output_%j.log       # Standard output log file
#SBATCH --error=error_%j.log         # Standard error log file

# Load required modules
module load StdEnv/2020
module load gcc/9.3.0
module load openmpi/4.0.3
module load openfoam/9              # Load OpenFOAM version 10

# Source the OpenFOAM environment
source $(echo $FOAM_ETC)/bashrc
# Navigate to the solver directory
cd /home/pasha77/scratch/karmaSolver
# Compile the custom solver
wmake
# Decompose the domain for parallel execution
cd /home/pasha77/scratch
rm -rf processor* *.log
blockMesh
decomposePar
# Run the OpenFOAM solver in parallel
srun karmaSolver -parallel