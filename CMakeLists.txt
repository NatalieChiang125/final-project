cmake_minimum_required(VERSION 3.27)
project(2025_I2P2_TowerDefense)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(Resource)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/External)

file(COPY Resource/audios DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/fonts DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource/images DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY Resource DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY allegro_monolith-5.2.dll DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_executable(2025_I2P2_TowerDefense
    Bullet/Bullet.cpp
    Bullet/Bullet.hpp
    Bullet/FireBullet.cpp
    Bullet/FireBullet.hpp
    Bullet/LaserBullet.cpp
    Bullet/LaserBullet.hpp
    Bullet/BoomBullet.cpp
    Bullet/BoomBullet.hpp
    Bullet/TurretFire.cpp
    Bullet/TurretFire.hpp
    Bullet/Rocket.cpp
    Bullet/Rocket.hpp

    Player/Player.cpp
    Player/Player.hpp

    # TODO HACKATHON-3 (3/3): Add the new enemy source files here(okay)
    Enemy/Enemy.cpp
    Enemy/Enemy.hpp
    Enemy/SoldierEnemy.cpp
    Enemy/SoldierEnemy.hpp
    Enemy/PlaneEnemy.cpp
    Enemy/PlaneEnemy.hpp
    Enemy/TankEnemy.cpp
    Enemy/TankEnemy.hpp
    Enemy/BoomEnemy.cpp
    Enemy/BoomEnemy.hpp
    Enemy/NoteEnemy.cpp
    Enemy/NoteEnemy.hpp

    Engine/Allegro5Exception.cpp
    Engine/Allegro5Exception.hpp
    Engine/AudioHelper.cpp
    Engine/AudioHelper.hpp
    Engine/Collider.cpp
    Engine/Collider.hpp
    Engine/GameEngine.cpp
    Engine/GameEngine.hpp
    Engine/Group.cpp
    Engine/Group.hpp
    Engine/IControl.cpp
    Engine/IControl.hpp
    Engine/IObject.cpp
    Engine/IObject.hpp
    Engine/IScene.cpp
    Engine/IScene.hpp
    Engine/LOG.cpp
    Engine/LOG.hpp
    Engine/Point.cpp
    Engine/Point.hpp
    Engine/Resources.cpp
    Engine/Resources.hpp
    Engine/Sprite.cpp
    Engine/Sprite.hpp
    Engine/GameTime.cpp
    Engine/GameTime.hpp
    Engine/PlayerStat.cpp
    Engine/PlayerStat.hpp
    Engine/map.cpp
    Engine/map.hpp
    Engine/Tile.cpp
    Engine/Tile.hpp
    
    # TODO HACKATHON-2 (3/3): Add the new scene source files here(okay)
    Scene/LoseScene.cpp
    Scene/LoseScene.hpp
    Scene/PlayScene.cpp
    Scene/PlayScene.hpp
    Scene/SettingsScene.cpp
    Scene/SettingsScene.hpp
    Scene/StageSelectScene.cpp
    Scene/StageSelectScene.hpp
    Scene/StartScene.cpp
    Scene/StartScene.h
    Scene/WinScene.cpp
    Scene/WinScene.hpp
    Scene/ScoreBoardScene.cpp
    Scene/ScoreBoardScene.hpp
    Scene/DailyScene.cpp
    Scene/DailyScene.hpp
    Scene/QuizScene.cpp
    Scene/QuizScene.hpp
    Scene/RhythmGameConfig.hpp
    Scene/RhythmGameScene.hpp
    Scene/RhythmGameScene.cpp
    Scene/ProgressScene.cpp
    Scene/ProgressScene.hpp

    Turret/LaserTurret.cpp
    Turret/LaserTurret.hpp
    Turret/MachineGunTurret.cpp
    Turret/MachineGunTurret.hpp
    Turret/FireTurret.cpp
    Turret/FireTurret.hpp
    Turret/Turret.cpp
    Turret/Turret.hpp
    Turret/TurretButton.cpp
    Turret/TurretButton.hpp
    Turret/Shovel.cpp
    Turret/Shovel.hpp
    Turret/ShieldTurret.cpp
    Turret/ShieldTurret.cpp

    

    UI/Animation/DirtyEffect.cpp
    UI/Animation/DirtyEffect.hpp
    UI/Animation/ExplosionEffect.cpp
    UI/Animation/ExplosionEffect.hpp
    UI/Animation/Plane.cpp
    UI/Animation/Plane.hpp

    UI/Component/Image.cpp
    UI/Component/Image.hpp
    UI/Component/ImageButton.cpp
    UI/Component/ImageButton.hpp
    UI/Component/Label.cpp
    UI/Component/Label.hpp
    UI/Component/Slider.cpp
    UI/Component/Slider.hpp

    ChatGPT_API/ChatGPT_API.cpp
    ChatGPT_API/ChatGPT_API.hpp
    
    main.cpp
)

# 加入 libcurl
#find_package(CURL REQUIRED)
set(CURL_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/third_party/curl/curl.h")
#set(CURL_LIBRARY "${CMAKE_SOURCE_DIR}/third_party/lib/libcurl.a")
set(CURL_LIBRARY_DLL "${CMAKE_SOURCE_DIR}/third_party/lib/libcurl.dll.a")
#target_include_directories(2025_I2P2_TowerDefense PRIVATE "${CURL_INCLUDE_DIR}")
target_link_libraries(2025_I2P2_TowerDefense PRIVATE "${CURL_LIBRARY}")
target_link_libraries(2025_I2P2_TowerDefense PRIVATE "${CURL_LIBRARY_DLL}")
#target_link_directories(2025_I2P2_TowerDefense PRIVATE "${CURL_LIB_DIR}")
#target_link_libraries(2025_I2P2_TowerDefense PRIVATE curl ws2_32)
target_link_libraries(2025_I2P2_TowerDefense PRIVATE ws2_32 wldap32 crypt32 normaliz advapi32)
# 平台特定設定
if (WIN32)
    target_include_directories(2025_I2P2_TowerDefense PRIVATE C:/allegro/include)
    target_link_directories(2025_I2P2_TowerDefense PRIVATE C:/allegro/lib)
    target_compile_options(2025_I2P2_TowerDefense PRIVATE ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense PRIVATE liballegro_monolith)
else()
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(ALLEGRO5 REQUIRED allegro-5 allegro_main-5 allegro_font-5 allegro_dialog-5 allegro_primitives-5 allegro_image-5 allegro_ttf-5 allegro_audio-5 allegro_acodec-5)
    target_include_directories(2025_I2P2_TowerDefense PRIVATE ${ALLEGRO5_INCLUDE_DIRS})
    target_compile_options(2025_I2P2_TowerDefense PRIVATE ${ALLEGRO5_CFLAGS_OTHER})
    target_link_libraries(2025_I2P2_TowerDefense PRIVATE ${ALLEGRO5_LIBRARIES})
    target_link_directories(2025_I2P2_TowerDefense PRIVATE ${ALLEGRO5_LIBRARY_DIRS})
endif()