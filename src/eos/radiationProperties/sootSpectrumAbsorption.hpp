#ifndef ABLATELIBRARY_SOOTSPECTRUMABSORPTION_HPP
#define ABLATELIBRARY_SOOTSPECTRUMABSORPTION_HPP

#include "eos/tChemSoot.hpp"
#include "finiteVolume/compressibleFlowFields.hpp"
#include "radiationProperties.hpp"
#include "utilities/constants.hpp"

namespace ablate::eos::radiationProperties {
class SootSpectrumAbsorption : public RadiationModel {
   private:
    struct FunctionContext {
        PetscInt densityYiCSolidCOffset;
        const ThermodynamicFunction temperatureFunction;
        const ThermodynamicTemperatureFunction densityFunction;
        const PetscReal minLambda = 0.4E-6;
        const PetscReal maxLambda = 30E-6;  //! These parameters could potentially be made into optional inputs and varied if we are interested in only part of the spectrum.
    };
    const std::shared_ptr<eos::EOS> eos;     //! eos is needed to compute field values
    constexpr static PetscReal rhoC = 2000;  // kg/m^3
    constexpr static PetscReal C_2 = (utilities::Constants::h * utilities::Constants::c) / (utilities::Constants::k);
    constexpr static PetscReal C_1 = NAN;  // TODO: Update this
    constexpr static PetscReal C_0 = 7.0;

   public:
    SootSpectrumAbsorption(std::shared_ptr<eos::EOS> eosIn);

    ThermodynamicFunction GetRadiationPropertiesFunction(RadiationProperty property, const std::vector<domain::Field>& fields) const;
    ThermodynamicTemperatureFunction GetRadiationPropertiesTemperatureFunction(RadiationProperty property, const std::vector<domain::Field>& fields) const;
    static PetscErrorCode SootFunction(const PetscReal* conserved, PetscReal* kappa, void* ctx);
    static PetscErrorCode SootTemperatureFunction(const PetscReal* conserved, PetscReal temperature, PetscReal* kappa, void* ctx);

};
}  // namespace ablate::eos::radiationProperties

#endif  // ABLATELIBRARY_SOOTSPECTRUMABSORPTION_HPP
