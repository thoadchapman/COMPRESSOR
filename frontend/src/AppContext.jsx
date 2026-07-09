import { createContext, useContext, useState } from 'react';

const AppContext = createContext();

export const AppProvider = ({ children }) => {
  const PORTA = "8080";
  const SERVIDOR_ID = "localhost:" + PORTA;
  const URL_BASE = `http://${SERVIDOR_ID}`;
  const [descomprimida, setDecomprimida] = useState();
  const [comprimida, setComprimida] = useState();
  const [original, setOriginal] = useState();
  return (
    <AppContext.Provider value={{ URL_BASE, descomprimida, setDecomprimida, comprimida, setComprimida, original, setOriginal }}>
      {children}
    </AppContext.Provider>
  );
};

export const useApp = () => {
  const context = useContext(AppContext);
  return context;
};