class Valve{
    private:
        bool status;
    public:
        Valve(bool status=false);
        void open_valve();
        void close_valve();
        bool statused()const;



};