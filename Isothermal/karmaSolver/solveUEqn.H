
#include "fvCFD.H"
#include "volFields.H"
#include "dimensionedScalar.H"
// #include "laplacianScheme.H"
#include "fvSchemes.H"
void solveUEqn(volScalarField& u, volScalarField& psi,dimensionedScalar& D_u, scalar k,dimensionedScalar&  W0  ,Time& runTime)
{
    Info << "Solving U equation at time = " << runTime.timeName() << endl;
    // Calculate coefficients
    volScalarField coeff = (1 + k - (1 - k) * psi) / 2;
    volScalarField gradPhiMag = mag(fvc::grad(psi));
    dimensionedScalar SMALL("SMALL", gradPhiMag.dimensions(), 1e-12);
    volVectorField normalizedGradPhi = fvc::grad(psi) / (gradPhiMag + SMALL);

    // Define the diffusion term
    volScalarField diffTerm = D_u * (1 - psi) / 2;  

    volVectorField Term2 = W0 / (2.0 * pow(2, 0.5)) * (1 + (1 - k) * u) *fvc::ddt(psi) * normalizedGradPhi;

    // Define the equation
    fvScalarMatrix UEqn
    (
        fvm::ddt(coeff, u)
    );
    // Add other terms
    // surfaceVectorField diffTermInterpolated = fvc::interpolate(diffTerm);
    UEqn += fvm::laplacian(diffTerm, u);
    UEqn += fvc::div(Term2);
    UEqn += (1 + (1 - k) * u) / 2 * fvc::ddt(psi);
    // Apply under-relaxation to the equation (if needed)
    UEqn.relax();
    // Solve the equation
    UEqn.solve();
    Info << "Finished solving U equation" << endl;
}


