// Copyright (c) 2017 Evgeniy Filimonov (evgfilim1@yandex.ru)
// Licensed under the GPLv3 license as published by Free Software Foundation.
// https://www.gnu.org/licenses/gpl-3.0-standalone.html

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

void CheckList::add(const CheckListTypes::IDType id, const CheckListTask& task) {
    bool created = false;
    try {
        this->m_data.at(id);
    } catch (std::out_of_range&) {
        this->m_data[id] = task;
        created = true;
    }
    if (!created) {
        throw std::logic_error("Element with such ID already exists");
    }
}
