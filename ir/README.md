sending part goes like this:

raw data code (010101...) => encode (NEC protocol, etc) => modulation


For `ac_ctrl` to actually work, you need rf24 library for sending instruction
to my arduino, because the real IR control for my AC is done there.
