#pragma once

class Favorite {

private:
    int userId;
    int mediaId;

public:

    Favorite() = default;

    Favorite(int userId, int mediaId)
        : userId(userId), mediaId(mediaId) {}

    int getUserId() const { return userId; }

    int getMediaId() const { return mediaId; }
};