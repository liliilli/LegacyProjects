package Custom;

public class Pair<T, U> {
    private int hash;

    private T lhv;
    private U rhv;

    public Pair(T lhv, U rhv) {
        this.lhv = lhv;
        this.rhv = rhv;
    }
    public Pair(Pair<T, U> original) {
        this.lhv = original.getFirst();
        this.rhv = original.getSecond();
        this.hash = original.hash;
    }

    public T getFirst() { return lhv; }
    public void setFirst(T lhv) { this.lhv = lhv; }

    public U getSecond() { return rhv; }
    public void setSecond(U rhv) { this.rhv = rhv; }

    public boolean equals(Object obj) {
        if (this == obj)
            return true;

        try {
            Pair<T, U> another = (Pair<T, U>)obj;
            return lhv == another.getFirst()
                    && rhv == another.getSecond();
        }
        catch (ClassCastException err) {
            return false;
        }
    }

    @Override
    public int hashCode() {
        int h = hash;
        if (h == 0) {
            String first = getFirst().toString();
            for (int i = 0; i < first.length(); ++i) {
                h = 31 * h + first.charAt(i);
            }
            String second = getSecond().toString();
            for (int i = 0; i < second.length(); ++i) {
                h = 48 * h + second.charAt(i);
            }
        }

        return h;
    }
}
