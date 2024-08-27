#include "fvCFD.H"
#include "solveUEqn.H"
#include "solvePsiEquation.H"
#include "epsilon.H"
#include "theta.H"
#include "InitialCond.H"
int main(int argc, char *argv[])
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"
    #include "createFields.H"
    // initializeFields(psi, u, mesh, radius, delta);

        forAll(psi, cellI)
    {
        const point& pt = mesh.C()[cellI];  // Get the cell center point

        if (pow(pt.x(), 2) + pow(pt.y(), 2) < pow(radius, 2) )
        {
            psi[cellI] = 1.0;
            u[cellI] =  - delta; // solid
        }
        else
        {
            psi[cellI] = -1.0;
            u[cellI] = -delta; // liquid
        }
    }
    // Manually write the fields to the disk
    psi.write();
    u.write();

    runTime.write();  // Write the initial conditions to the 0 time step

    while (runTime.loop())
    {
        Info << "Time = " << runTime.timeName() << nl << endl;
        /////////////////////////// Solve the Karma model //////////////////////////////
        calculateTheta(psi, theta);
        calculateEpsilon(theta, W0, ep4, anisotropy, epsilon);
        calculateEpsilonDerivative(theta, W0, ep4, anisotropy, epsilonDerivative);
        // Solve the equation for psi
        solvePhiEquation(psi, epsilon, epsilonDerivative, u, lambda, tau0, W0 ,runTime);
        // Solve the equation for u
        solveUEqn(u, psi, D_u, k, W0, runTime);
        //////////////////////////////////  END    /////////////////////////////////////
        runTime.write();  // Write the results
        Info << "ExecutionTime = " << runTime.elapsedCpuTime() << " s" << nl
             << "ClockTime = " << runTime.elapsedClockTime() << " s" << nl << endl;
    }

    Info << "End\n" << endl;
    return 0;
}
