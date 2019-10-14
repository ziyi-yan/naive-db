#ifndef NAIVE_DB_ROW_H
#define NAIVE_DB_ROW_H

#include <cstdint>
#include <string>

struct Row {
  enum : uint32_t {
    ID_SIZE = 4,
    USERNAME_SIZE = 32,
    EMAIL_SIZE = 255,
    ROW_SIZE = ID_SIZE + USERNAME_SIZE + EMAIL_SIZE,

    ID_OFFSET = 0,
    USERNAME_OFFSET = ID_OFFSET + ID_SIZE,
    EMAIL_OFFSET = USERNAME_OFFSET + USERNAME_SIZE,
  };

  uint32_t id;
  char username[USERNAME_SIZE+1];
  char email[EMAIL_SIZE+1];

  void serializeTo(uint8_t *dst);
  void deserializeFrom(uint8_t *src);
};


#endif  // NAIVE_DB_ROW_H
