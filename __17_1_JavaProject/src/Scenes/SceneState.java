package Scenes;

public enum SceneState {
    NORMAL(0x1000),
    FOCUS_LOGPANEL(0x1010),
    FOCUS_MESSAGE(0x1020),
    SCENE_MOVE(0x1030),
    // 각 장면마다 쓰일 수 있는 로컬 상태
    A(0x4000),
    B(0x4010),
    C(0x4020),
    D(0x4030),
    SOMETHING_ELSE(0xFFFF);

    private final int value;
    SceneState(int i) { this.value = i; }
}
