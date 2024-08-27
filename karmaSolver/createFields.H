// Create scalar field for psi
volScalarField psi
(
    IOobject
    (
        "psi",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
volScalarField u
(
    IOobject
    (
        "u",
        runTime.timeName(),
        mesh,
        IOobject::MUST_READ,
        IOobject::AUTO_WRITE
    ),
    mesh
);
// Create scalar field for theta
volScalarField theta
(
    IOobject
    (
        "theta",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,  
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimensionSet(0, 0, 0, 0, 0, 0, 0), 0.0) // Initialize to zero
);
// Create scalar field for epsilonDerivative
volScalarField epsilonDerivative
(
    IOobject
    (
        "epsilonDerivative",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimensionSet(0, 1, 0, 0, 0), 0.0) // Initialize to zero
);
// Create scalar field for epsilon
volScalarField epsilon
(
    IOobject
    (
        "epsilon",
        runTime.timeName(),
        mesh,
        IOobject::NO_READ,  // Set to NO_READ if calculated internally, change to MUST_READ if initialized from a file
        IOobject::NO_WRITE
    ),
    mesh,
    dimensionedScalar("zero", dimensionSet(0, 1, 0, 0, 0), 0.0) // Initialize to zero, will be calculated based on theta
);
dimensionedScalar D_u("D_u", dimensionSet(0, 2, -1, 0, 0), 2.0); // Corrected dimensions for diffusivity [L^2 T^-1]
dimensionedScalar tau0("tau0", dimensionSet(0, 0, 1, 0, 0), 1.0);  // Corrected dimensions for tau0 [T]
dimensionedScalar W0("W0", dimensionSet(0, 1, 0, 0, 0), 1.0);    
dimensionedScalar ep4("ep4", dimensionSet(0, 0, 0, 0, 0), 0.02);
dimensionedScalar lambda("lambda", dimensionSet(0, 0, 0, 0, 0), 3.1913); // Lambda is dimensionless
dimensionedScalar anisotropy("anisotropy", dimensionSet(0, 0, 0, 0, 0), 4.0); // Mode number of anisotropy [dimensionless]
scalar k = 0.15;
scalar radius = 20.0;  // this is the radius of the solid circle squared
scalar delta = 0.55;  // this is the initial value of u in the liquid region or omega






