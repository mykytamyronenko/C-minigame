#ifndef STATE_H
#define STATE_H


class State
{
    private:

    public:
        State();
        virtual ~State();
        virtual void update() = 0;
        virtual void render() = 0;
        virtual void handleInput() = 0;



};

#endif // STATE_H
