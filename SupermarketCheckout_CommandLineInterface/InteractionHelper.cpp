#include "InteractionHelper.hpp"

#include "DefaultInteraction.hpp"
#include "InputInteraction.hpp"

std::unique_ptr<InteractionHelper> constructInteractionHelper(InteractionMode interactionMode)
{
	switch (interactionMode)
	{
	case InteractionMode::Default: return std::make_unique<DefaultInteraction>();
	case InteractionMode::Customize: return std::make_unique<CLIInputInteraction>();
	default: return std::make_unique<DefaultInteraction>();
	}
}