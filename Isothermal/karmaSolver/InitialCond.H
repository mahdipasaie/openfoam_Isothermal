// Function to initialize psi and u fields
#include "fvCFD.H"

void initializeFields(volScalarField& psi, volScalarField& u, const fvMesh& mesh, scalar radius, scalar delta)
{
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
}
