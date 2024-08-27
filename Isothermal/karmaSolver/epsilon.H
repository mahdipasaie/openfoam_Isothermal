
#include "volFields.H"
#include "fvCFD.H"
#include "dimensionedScalar.H"

// Function to calculate epsilon(theta)
void calculateEpsilon(
    const volScalarField& theta,         // Input field for theta
    const dimensionedScalar& W0, // Base value of epsilon
    const dimensionedScalar& ep4,      // Anisotropy strength
    const dimensionedScalar& anisotropy, // Anisotropy mode number
    volScalarField& epsilon              // Reference to the result field
)
{
    // Calculate epsilon = w0 * (1.0 + ep4 * cos(anisotropy * theta))
    epsilon = W0 * (1.0 + ep4 * Foam::cos(anisotropy * theta));

    // Optional: Write the epsilon field to disk for post-processing
}

// Function to calculate the derivative of epsilon with respect to theta
void calculateEpsilonDerivative(
    const volScalarField& theta,         // Input field for theta
    const dimensionedScalar& W0, // Base value of epsilon
    const dimensionedScalar& ep4,      // Anisotropy strength
    const dimensionedScalar& anisotropy, // Anisotropy mode number
    volScalarField& epsilonDerivative    // Reference to the result field
)
{
    // Calculate epsilonDerivative = -w0 * anisotropy * ep4 * sin(anisotropy * theta)
    epsilonDerivative = -W0 * anisotropy * ep4 * Foam::sin(anisotropy * theta);


    // Optional: Write the epsilonDerivative field to disk for post-processing
}


