#ifndef PHI_EQUATION_H
#define PHI_EQUATION_H
#include "fvCFD.H"
#include "volFields.H"
#include "dimensionedScalar.H"
// Function to solve the phi equation
void solvePhiEquation(
    volScalarField& psi,                   // Field for phi
    volScalarField& epsilon,         // Field for epsilon(theta)
    volScalarField& epsilonDerivative, // Field for epsilon'(theta)
    volScalarField& u,                 // Field for u
    dimensionedScalar& lambda, 
    dimensionedScalar& tau0,          // Diffusion coefficient for u
    dimensionedScalar& W0,
    Time& runTime                   // Time object for simulation time
)
{
    // Compute the gradient of phi
    volVectorField gradPhi = fvc::grad(psi);
    // Calculate the diffusion term: div(epsilon^2 * grad(phi))
    // volScalarField diffusionTerm = fvc::div(epsilon * epsilon * gradPhi); 
    fvScalarMatrix diffusionTerm = fvm::laplacian(epsilon * epsilon, psi);
    // Calculate the cross terms:
    volVectorField TermX = fvc::grad(epsilon * epsilonDerivative * gradPhi.component(vector::Y));
    volVectorField TermY= fvc::grad(epsilon * epsilonDerivative * gradPhi.component(vector::X));
    volScalarField TermX_X = TermX.component(vector::X);
    volScalarField TermY_Y = TermY.component(vector::Y);
    volScalarField epsilonSquared = epsilon/W0 * epsilon/W0 ;
     // Define the PDE using fvScalarMatrix
    fvScalarMatrix phiEqn(
        tau0 * epsilonSquared * fvm::ddt(psi)                                    // Time derivative
        - diffusionTerm                                      // Diffusion term
        + TermX_X                                            // Cross term in x-direction
        - TermY_Y                                            // Cross term in y-direction
        - (psi - pow(psi,3) )
        - lambda * u * pow((1 - psi* psi),2)
    );
    // Relax and solve the equation
    phiEqn.relax();
    phiEqn.solve();
}

#endif
