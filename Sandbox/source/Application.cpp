/*
 * Copyright (c) Kaloyan Badankov
 */

namespace Sirius {

_declspec(dllimport) void Print();

} // namespace Sirius

void main() {
    Sirius::Print();
    Sirius::Print();
}
