#include "MultipleChoiceCreator.h"

std::unique_ptr<Question> MultipleChoiceCreator::CreateQuestion(const std::string& text)
{
    return std::make_unique<MultipleChoice>(text);
}