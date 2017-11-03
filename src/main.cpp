int main()
{
    // create our window
    main_window my_window;

    // tell our window to put itself on the screen
    my_window.show();

    // wait until the user closes this window before we let the program 
    // terminate.
    my_window.wait_until_closed();
}
