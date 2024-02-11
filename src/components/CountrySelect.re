open Dropdown;
open DropdownMenu;
open DropdownTrigger;
open Types;

module type Utils = {
  let decodeCountriesResponse: Js.Json.t => array(Types.country);
  let sortCountries: (Types.country, Types.country) => int;
};
module Utils: Utils = {
  let decodeCountryFields = (obj): Types.country => {
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
    let activeUsers =
      Js.Dict.get(obj, "users")
      ->Belt.Option.map(value =>
          value |> Js.Json.decodeNumber |> Belt.Option.getExn |> int_of_float
        );

    {
      label,
      value,
      extraFields: {
        activeUsers: activeUsers,
      },
    };
  };
  let decodeCountriesResponse = (json: Js.Json.t) =>
    json
    |> Js.Json.decodeArray
    |> (opt => Belt.Option.getExn(opt))
    |> (
      items =>
        items
        |> Array.map(item =>
             item
             |> Js.Json.decodeObject
             |> Belt.Option.getExn
             |> decodeCountryFields
           )
    );
  let sortCountries = (a: Types.country, b: Types.country) => {
    switch (a.extraFields.activeUsers, b.extraFields.activeUsers) {
    | (Some(_), None) => (-1)
    | (None, Some(_)) => 1
    | (Some(activeUsersA), Some(activeUsersB)) =>
      activeUsersB - activeUsersA
    | (None, None) =>
      if (a.label < b.label) {
        (-1);
      } else if (a.label > b.label) {
        1;
      } else {
        0;
      }
    };
  };
};
module Constants = {
  let countriesUrl = "https://gist.githubusercontent.com/rusty-key/659db3f4566df459bd59c8a53dc9f71f/raw/4127f9550ef063121c564025f6d27dceeb279623/counties.json";
};

module type CountrySelect = {
  [@react.component]
  let make:
    (
      ~country: option(string),
      ~onChange: string => unit,
      ~className: string=?
    ) =>
    React.element;
};
module CountrySelect: CountrySelect = {
  [@react.component]
  let make = (~country, ~onChange, ~className=?) => {
    let (isOpen, setIsOpen) = React.useState(() => false);
    let (options, setOptions) = React.useState(() => [||]);

    React.useEffect0(() => {
      let fetch = () =>
        Js.Promise.(
          Fetch.fetch(Constants.countriesUrl)
          |> then_(Fetch.Response.json)
          |> then_(json =>
               json
               |> Utils.decodeCountriesResponse
               |> (
                 decodedArray =>
                   {
                     Array.sort(Utils.sortCountries, decodedArray);
                     setOptions(_ => decodedArray);
                   }
                   |> resolve
               )
             )
        );

      ignore(fetch());
      None;
    });

    let selectedOption =
      options->Belt.Array.getBy(optionsItem =>
        country
        ->Belt.Option.map(c => c === optionsItem.value)
        ->Belt.Option.getWithDefault(false)
      );

    let handleTriggerClick = _ => {
      if (isOpen) {()};
      setIsOpen(_ => true);
    };
    let triggerRef = React.useRef(Js.Nullable.null);
    let focusTrigger = () => {
      switch (Js.Nullable.toOption(triggerRef.current)) {
      | Some(elem) =>
        elem
        ->Webapi.Dom.HtmlElement.ofElement
        ->Belt.Option.map(Webapi.Dom.HtmlElement.focus)
        ->Belt.Option.getWithDefault()
      | None => ()
      };
    };
    let trigger =
      <DropdownTrigger
        innerRef={ReactDOM.Ref.domRef(triggerRef)}
        selectedOption
        onClick=handleTriggerClick
      />;

    let handleOnClose = () => {
      setIsOpen(_ => false);
      focusTrigger();
    };
    let handleValueChange = (newCountry: Types.countryJsCompatible) => {
      onChange(Types.countryJsToCountry(newCountry).value);
      handleOnClose();
    };

    let selectedOptionJs =
      selectedOption->Belt.Option.map(Types.countryToCountryJs)
      |> Js.Nullable.fromOption;
    let optionsJs = Array.map(Types.countryToCountryJs, options);

    <Dropdown
      className={Belt.Option.getWithDefault(className, "")}
      isOpen
      trigger
      onClose=handleOnClose>
      <DropdownMenu
        options=optionsJs
        value=selectedOptionJs
        onChange=handleValueChange
      />
    </Dropdown>;
  };
};
