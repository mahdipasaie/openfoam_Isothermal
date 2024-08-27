
void calculateTheta(
    const volScalarField& psi,  // Input field for phi
    volScalarField& theta       // Reference to the result field
)
{
    // Calculate the gradient of phi
    volVectorField gradPhi = fvc::grad(psi);

    // Calculate theta = atan2(gradPhi_y, gradPhi_x)
    theta = Foam::atan2(gradPhi.component(1), gradPhi.component(0));

}
