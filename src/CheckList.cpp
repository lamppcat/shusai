#include "../include/CheckList.h"

CheckListTypes::IDType CheckList::index(const CheckListTypes::string caption, const bool checked) const {
    const CheckListTask another(caption, checked);
    return this->index(another);
}

CheckListTypes::IDType CheckList::index(const CheckListTask& task) const {
    for (const auto& item : this->m_data) {
        if (item.second == task) {
            return item.first;
        }
    }
    throw std::out_of_range("Target element was not found");
}

CheckListTask CheckList::pop(CheckListTypes::IDType idx) {
    const CheckListTask result = this->at(idx);
    this->remove(idx);
    return result;
}

void CheckList::add(const CheckListTypes::IDType id, const CheckListTypes::string& caption, const bool checked) {
    const CheckListTask another(caption, checked);
    this->add(id, another);
}
