module App = {
  type country = {
    .
    "label": string,
    "value": string,
  };

  [@react.component]
  let make = () => {
    let style =
      ReactDOM.Style.make(
        ~height="100vh",
        ~width="100vw",
        ~display="flex",
        ~justifyContent="center",
        ~alignItems="center",
        (),
      );

    let (countries, setCountries) = React.useState(() => None);
    React.useEffect0(() => {
      let decodeFields = (obj): country => {
        let label =
          Js.Dict.get(obj, "label")
          |> Belt.Option.getExn
          |> Js.Json.decodeString
          |> Belt.Option.getExn;
        let value =
          Js.Dict.get(obj, "value")
          |> Belt.Option.getExn
          |> Js.Json.decodeString
          |> Belt.Option.getExn;

        {"label": label, "value": value};
      };
      let fetch = () =>
        Js.Promise.(
          Fetch.fetch(
            "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json",
          )
          |> then_(Fetch.Response.json)
          |> then_(json => Js.Json.decodeArray(json) |> resolve)
          |> then_(opt => Belt.Option.getExn(opt) |> resolve)
          |> then_(items =>
               items
               |> Array.map(item =>
                    item
                    |> Js.Json.decodeObject
                    |> Belt.Option.getExn
                    |> decodeFields
                  )
               |> resolve
             )
          |> then_(decodedList => {
               setCountries(_ => Some(decodedList));
               resolve();
             })
        );

      ignore(fetch());
      None;
    });

    let content =
      switch (countries) {
      | None => React.null
      | Some(options) => <ReactSelect options />
      };

    <div style> content </div>;
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
