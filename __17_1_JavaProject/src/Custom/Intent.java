package Custom;

import java.util.HashMap;
import java.util.Map;

public class Intent {
    private static Intent instance = null;
    private Map<String, Object> extraInformation = new HashMap<>();
    private Intent() {};

    public synchronized <T> Intent add(String tag, T object) {
        extraInformation.put(tag, object);
        return this;
    }

    public synchronized Object get(String tag) {
        return extraInformation.get(tag);
    }

    public static synchronized void removeIntent() { instance = null; }

    public static synchronized Intent getIntent() {
        return instance != null ? instance : newIntent();
    }

    public static synchronized Intent newIntent() {
        if (instance == null)
            instance = new Intent();

        return instance;
    }
}
