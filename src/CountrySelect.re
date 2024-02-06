module Types = {
  type countryJsCompatible = {
    label: string,
    value: string,
    users: Js.Nullable.t(int),
  };

  type country = {
    label: string,
    value: string,
    users: option(int),
  };

  let countryToCountryJs = (c: country): countryJsCompatible => {
    {
      label: c.label,
      value: c.value,
      users:
        switch (c.users) {
        | None => Js.Nullable.null
        | Some(users) => Js.Nullable.return(users)
        },
    };
  };

  let countryJsToCountry = (c: countryJsCompatible): country => {
    {label: c.label, value: c.value, users: Js.Nullable.toOption(c.users)};
  };
};

module ReactSelect = {
  type customStylesMap('a) = {
    container: 'a,
    control: 'a,
    input: 'a,
    menu: 'a,
    menuList: 'a,
    option: 'a,
    placeholder: 'a,
    valueContainer: 'a,
  };

  type optionState = {
    isFocused: bool,
    isSelected: bool,
  };

  type stylesType =
    customStylesMap((ReactDOM.Style.t, optionState) => ReactDOM.Style.t);

  [@mel.module "react-select"] [@react.component]
  external make:
    (
      ~options: array(Types.countryJsCompatible),
      ~value: option(Types.countryJsCompatible),
      ~onChange: Types.countryJsCompatible => unit,
      ~styles: stylesType,
      ~menuIsOpen: bool,
    ) =>
    React.element =
    "default";
};

module CountrySelect = {
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
      let users =
        Js.Dict.get(obj, "users")
        ->Belt.Option.map(value =>
            value |> Js.Json.decodeNumber |> Belt.Option.getExn |> int_of_float
          );

      {label, value, users};
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
      switch (a.users, b.users) {
      | (Some(_), None) => (-1)
      | (None, Some(_)) => 1
      | (Some(usersA), Some(usersB)) => usersB - usersA
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

    type colors = {
      // background: string,
      backgroundSelected: string,
      // borderDark: string,
      borderLight: string,
      shadow: string,
      textPrimary: string,
      // textSecondary: string,
      textTertiary: string,
    };
    let colors = {
      // background: "#FFFFFF",
      backgroundSelected: "#FFDBB3",
      // borderDark: "#00000033",
      borderLight: "#00000014",
      shadow: "rgba(0, 0, 0, 0.15)",
      textPrimary: "#333333",
      // textSecondary: "#00000085",
      textTertiary: "#00000052",
    };
  };

  module Styles = {
    let makeStyleWithTextPrimary =
      ReactDOM.Style.make(
        ~fontFamily="Arial",
        ~fontSize="14px",
        ~fontStyle="normal",
        ~fontWeight="400",
        ~lineHeight="18px",
      );

    let customStyles: ReactSelect.customStylesMap(ReactDOM.Style.t) = {
      container:
        ReactDOM.Style.make(
          ~width="230px",
          ~color=Constants.colors.textPrimary,
          (),
        ),
      control:
        ReactDOM.Style.make(
          ~flexDirection="row-reverse",
          ~minHeight="26px",
          ~padding="0px 10px",
          ~alignItems="center",
          ~flexShrink="0",
          ~alignSelf="stretch",
          ~height="38px",
          ~borderRadius="2px",
          ~borderStyle="none",
          ~borderWidth="1px",
          ~borderBottomLeftRadius="0",
          ~borderBottomRightRadius="0",
          ~boxShadow=
            "0px 3px 18px 0px "
            ++ Constants.colors.shadow
            ++ ", 0px 0px 0px 1px "
            ++ Constants.colors.borderLight,
          (),
        ),
      input: makeStyleWithTextPrimary(),
      menu:
        ReactDOM.Style.make(
          ~margin="0",
          ~borderRadius="2px",
          ~borderStyle="none",
          ~borderWidth="1px",
          ~borderTopLeftRadius="0",
          ~borderTopRightRadius="0",
          ~boxShadow=
            "0px 7px 14px -2px "
            ++ Constants.colors.shadow
            ++ ", 0px 0px 0px 1px "
            ++ Constants.colors.borderLight,
          (),
        ),
      menuList: ReactDOM.Style.make(~maxHeight="365px", ()),
      option:
        makeStyleWithTextPrimary(
          ~padding="4px 6px 4px 10px",
          ~color=Constants.colors.textPrimary,
          (),
        ),
      placeholder:
        makeStyleWithTextPrimary(
          ~height="18px",
          ~flex="1 0 0",
          ~overflow="hidden",
          ~color=Constants.colors.textTertiary,
          ~textOverflow="ellipsis",
          ~whiteSpace="nowrap",
          (),
        ),
      valueContainer:
        ReactDOM.Style.make(
          ~padding="0",
          ~height="28px",
          ~fontSize="14px",
          ~alignItems="center",
          (),
        ),
    };
  };

  [@react.component]
  let make =
      // (~country: string, ~onChange: string => unit, ~className: string=?) => {
      (~country: option(string), ~onChange: string => unit) => {
    // let (isOpen, setIsOpen) = React.useState(() => false);
    let (options, setOptions) = React.useState(() => [||]);
    // let handleOnClose = () => setIsOpen(_ => false);
    let handleValueChange = (newCountry: Types.countryJsCompatible) => {
      onChange(
        Types.countryJsToCountry(newCountry).value,
        // handleOnClose();
      );
    };

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

    let selectedCountryJs =
      Belt.Option.flatMap(country, c =>
        Belt.Array.getBy(options, item => item.value === c)
        ->Belt.Option.map(Types.countryToCountryJs)
      );

    let optionsJs = Array.map(Types.countryToCountryJs, options);

    <ReactSelect
      options=optionsJs
      value=selectedCountryJs
      onChange=handleValueChange
      styles={
        container: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.container),
        control: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.control),
        input: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.input),
        menu: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.menu),
        menuList: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.menuList),
        option: (baseStyles, state) => {
          Js.log("state = ");
          Js.log(state.isFocused);
          Js.log(state.isSelected);
          baseStyles
          -> ReactDOM.Style.combine(Styles.customStyles.option)
          -> ReactDOM.Style.combine(
               if (state.isFocused || state.isSelected) {
                 ReactDOM.Style.make(
                   ~backgroundColor=Constants.colors.backgroundSelected,
                   (),
                 );
               } else {
                 ReactDOM.Style.make();
               },
             );
        },
        placeholder: (baseStyles, _) =>
          ReactDOM.Style.combine(baseStyles, Styles.customStyles.placeholder),
        valueContainer: (baseStyles, _) =>
          ReactDOM.Style.combine(
            baseStyles,
            Styles.customStyles.valueContainer,
          ),
      }
      menuIsOpen=true
    />;
  };
};
