#include "WordCreator.h"

std::unique_ptr<Question> WordCreator::CreateQuestion(const std::string& text)
{
    return std::make_unique<Word>(text);
}
