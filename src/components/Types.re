module Types = {
  type extraFieldsJsCompatible = {activeUsers: Js.Nullable.t(int)};
  type countryJsCompatible = {
    label: string,
    value: string,
    extraFields: extraFieldsJsCompatible,
  };
  type extraFields = {activeUsers: option(int)};
  type country = {
    label: string,
    value: string,
    extraFields,
  };
  let countryToCountryJs = (c: country): countryJsCompatible => {
    {
      label: c.label,
      value: c.value,
      extraFields: {
        activeUsers: Js.Nullable.fromOption(c.extraFields.activeUsers),
      },
    };
  };
  let countryJsToCountry = (c: countryJsCompatible): country => {
    {
      label: c.label,
      value: c.value,
      extraFields: {
        activeUsers: Js.Nullable.toOption(c.extraFields.activeUsers),
      },
    };
  };
};
