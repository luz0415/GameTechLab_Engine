#pragma once

class IPickable
{
public:
    virtual ~IPickable() = default;

    virtual void OnSelected() = 0;
    virtual void OnDeselected() = 0;
    virtual bool CanPickable() = 0;
};