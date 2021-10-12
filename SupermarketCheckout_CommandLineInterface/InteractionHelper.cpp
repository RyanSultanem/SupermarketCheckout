#include "InteractionHelper.hpp"

#include "DefaultInteraction.hpp"
#include "InputInteraction.hpp"

std::unique_ptr<InteractionHelper> constructInteractionHelper(InteractionMode interactionMode)
{
	switch (interactionMode)
	{
	case InteractionMode::Default: return std::make_unique<DefaultInteraction>();
	case InteractionMode::Manual: return std::make_unique<CLIInputInteraction>();
	case InteractionMode::File: return std::make_unique<FileInputInteraction>();
	default: return std::make_unique<DefaultInteraction>();
	}
}