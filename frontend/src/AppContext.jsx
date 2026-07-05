import { createContext, useContext, useState } from 'react';

const AppContext = createContext();

export const AppProvider = ({ children }) => {
  const PORTA = "8080";
  const SERVIDOR_ID = "localhost:" + PORTA;
  const URL_BASE = `http://${SERVIDOR_ID}`;

  const [decompressa, setDecompressa] = useState();
  const [compressa, setCompressa] = useState();  
  return (
    <AppContext.Provider value={{ URL_BASE, decompressa, setDecompressa, compressa, setCompressa }}>
      {children}
    </AppContext.Provider>
  );
};

export const useApp = () => {
  const context = useContext(AppContext);
  return context;
};