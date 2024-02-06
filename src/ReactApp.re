open CountrySelect;

module App = {
  let style =
    ReactDOM.Style.make(
      ~height="100vh",
      ~width="100vw",
      ~display="flex",
      ~justifyContent="center",
      ~alignItems="center",
      (),
    );

  [@react.component]
  let make = () => {
    let (country, setCountry) = React.useState(() => None);
    let handleCountryChange = (newCountry: string) => {
      setCountry(_ => Some(newCountry));
    };

    <div style> <CountrySelect country onChange=handleCountryChange /> </div>;
  };
};

ReactDOM.querySelector("#root")
->(
    fun
    | Some(root) => ReactDOM.render(<App />, root)
    | None =>
      Js.Console.error(
        "Failed to start React: couldn't find the #root element",
      )
  );
