#include "NumberCreator.h"

std::unique_ptr<Question> NumberCreator::CreateQuestion(const std::string& text)
{
    return std::make_unique<Number>(text);
}
